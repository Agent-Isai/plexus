/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  InspIRCd: (C) 2002-2007 InspIRCd Development Team
 * See: http://www.inspircd.org/wiki/index.php/Credits
 *
 * This program is free but copyrighted software; see
 *	    the file COPYING for details.
 *
 * ---------------------------------------------------
 */

#include "configreader.h"
#include "users.h"
#include "modules.h"
#include "wildcard.h"
#include "commands/cmd_who.h"

/* get the last 'visible' chan of a user */
static char *getlastchanname(userrec *u)
{
	UCListIter i = u->chans.begin();
	if (i != u->chans.end())
	{
		if (!i->first->IsModeSet('s'))
			return i->first->name;
	}

	return "*";
}

bool whomatch(userrec* user, const char* matchtext, bool opt_realname, bool opt_showrealhost, bool opt_mode)
{
	bool realhost = false;
	bool realname = false;
	bool positive = true;

	if (user->registered != REG_ALL)
		return false;

	if (opt_mode)
	{
		for (const char* n = matchtext; *n; n++)
		{
			if (*n == '+')
			{
				positive = true;
				continue;
			}
			else if (*n == '-')
			{
				positive = false;
				continue;
			}
			if (user->IsModeSet(*n) != positive)
				return false;
		}
		return true;
	}

	if (opt_realname)
		realname = match(user->fullname, matchtext);

	if (opt_showrealhost)
		realhost = match(user->host, matchtext);

	return ((realname) || (realhost) || (match(user->dhost, matchtext)) || (match(user->nick, matchtext)) || (match(user->server, matchtext)));
}



extern "C" command_t* init_command(InspIRCd* Instance)
{
	return new cmd_who(Instance);
}

bool cmd_who::CanView(chanrec* chan, userrec* user)
{
	if (!user || !chan)
		return false;

	/* Execute items in fastest-to-execute first order */

	/* Opers see all */
	if (*user->oper)
		return true;
	else if (!chan->IsModeSet('s') && !chan->IsModeSet('p'))
		return true;
	else if (chan->HasUser(user))
		return true;

	return false;
}

void cmd_who::SendWhoLine(userrec* user, const std::string &initial, chanrec* ch, userrec* u, std::vector<std::string> &whoresults)
{
	std::string lcn = getlastchanname(u);
	chanrec* chlast = ServerInstance->FindChan(lcn);

	/* Not visible to this user */
	if (u->Visibility && !u->Visibility->VisibleTo(user))
		return;

	std::string wholine =	initial + (ch ? ch->name : lcn) + " " + u->ident + " " + (opt_showrealhost ? u->host : u->dhost) + " " +
				((*ServerInstance->Config->HideWhoisServer && !*user->oper) ? ServerInstance->Config->HideWhoisServer : u->server) +
				" " + u->nick + " ";

	/* away? */
	if (*u->awaymsg)
	{
		wholine.append("G");
	}
	else
	{
		wholine.append("H");
	}

	/* oper? */
	if (*u->oper)
	{
		wholine.append("*");
	}

	wholine = wholine + (ch ? ch->GetPrefixChar(u) : (chlast ? chlast->GetPrefixChar(u) : "")) + " :0 " + u->fullname;
	whoresults.push_back(wholine);
}

CmdResult cmd_who::Handle (const char** parameters, int pcnt, userrec *user)
{
	/*
	 * XXX - RFC says:
	 *   The <name> passed to WHO is matched against users' host, server, real
	 *   name and nickname
	 * Currently, we support WHO #chan, WHO nick, WHO 0, WHO *, and the addition of a 'o' flag, as per RFC.
	 */

	/* WHO options */
	opt_viewopersonly = false;
	opt_showrealhost = false;
	opt_unlimit = false;
	opt_realname = false;
	opt_mode = false;

	chanrec *ch = NULL;
	std::vector<std::string> whoresults;
	std::string initial = "352 " + std::string(user->nick) + " ";

	const char* matchtext = NULL;

	/* Change '0' into '*' so the wildcard matcher can grok it */
	matchtext = parameters[0];
	if (!strcmp(matchtext,"0"))
		matchtext = "*";

	if (pcnt > 1)
	{
		/* parse flags */
		const char *iter = parameters[1];

		while (*iter)
		{
			switch (*iter)
			{
				case 'o':
					opt_viewopersonly = true;
				break;
				case 'h':
					if (*user->oper)
						opt_showrealhost = true;
				break;
				case 'u':
					if (*user->oper)
						opt_unlimit = true;
				break;
				case 'r':
					opt_realname = true;
				break;
				case 'm':
					opt_mode = true;
				break;
			}

			*iter++;
		}
	}


	/* who on a channel? */
	ch = ServerInstance->FindChan(matchtext);

	if (ch)
	{
		if (CanView(ch,user))
		{
			bool inside = ch->HasUser(user);
	
			/* who on a channel. */
			CUList *cu = ch->GetUsers();
	
			for (CUList::iterator i = cu->begin(); i != cu->end(); i++)
			{
				/* opers only, please */
				if (opt_viewopersonly && !*(i->second)->oper)
					continue;
	
				/* If we're not inside the channel, hide +i users */
				if (i->second->IsModeSet('i') && !inside)
					continue;
	
				SendWhoLine(user, initial, ch, i->second, whoresults);
			}
		}
	}
	else
	{
		/* Match against wildcard of nick, server or host */

		if (opt_viewopersonly)
		{
			/* Showing only opers */
			for (std::vector<userrec*>::iterator i = ServerInstance->all_opers.begin(); i != ServerInstance->all_opers.end(); i++)
			{
				userrec* oper = *i;

				if (whomatch(oper, matchtext, opt_realname, opt_showrealhost, opt_mode))
				{
					if (!oper->IsModeSet('i'))
						SendWhoLine(user, initial, NULL, oper, whoresults);
				}
			}
		}
		else
		{
			for (user_hash::iterator i = ServerInstance->clientlist->begin(); i != ServerInstance->clientlist->end(); i++)
			{
				if (whomatch(i->second, matchtext, opt_realname, opt_showrealhost, opt_mode))
				{
					if (!i->second->IsModeSet('i'))
						SendWhoLine(user, initial, NULL, i->second, whoresults);
				}
			}
		}
	}
	/* Send the results out */
	if ((whoresults.size() < (size_t)ServerInstance->Config->MaxWhoResults) && (!opt_unlimit))
	{
		for (std::vector<std::string>::const_iterator n = whoresults.begin(); n != whoresults.end(); n++)
			user->WriteServ(*n);
		user->WriteServ("315 %s %s :End of /WHO list.",user->nick, *parameters[0] ? parameters[0] : "*");
		return CMD_SUCCESS;
	}
	else
	{
		/* BZZT! Too many results. */
		user->WriteServ("315 %s %s :Too many results",user->nick, parameters[0]);
		return CMD_FAILURE;
	}
}

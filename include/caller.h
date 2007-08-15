/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  InspIRCd: (C) 2002-2007 InspIRCd Development Team
 * See: http://www.inspircd.org/wiki/index.php/Credits
 *
 * This program is free but copyrighted software; see
 *            the file COPYING for details.
 *
 * ---------------------------------------------------
 */

#ifndef __CALLER__H__
#define __CALLER__H__

/* The templates below can be auto generated by tools/create_templates.pl.
 * They are used to represent a functor with a given number of parameters and
 * a specific return type. To prevent passing the wrong number of parameters
 * and have the compiler detect this error at build-time, each class is numbered
 * according to the number of parameters it takes, e.g. caller0, caller1, caller2.
 * These have been generated from zero parameters to eight.
 *
 * If you want to declare a functor which takes two parameters, a userrec and a chanrec,
 * and returns bool, simply create it like this:
 *
 * caller2<bool, userrec*, chanrec*> MyFunction;
 *
 * and initialize it correctly, when placed into a class you will be able to call it:
 *
 * bool n = someclass->MyFunction(someuser, somechan);
 *
 * These functor templates work this way so that you can simply and easily allow
 * for these class methods to be overridden from within a module, e.g. have a module
 * which completely replaces the code f r IsNick, etc. For example, with the example
 * above:
 *
 * MyNewFunction replaceme(ServerInstance);
 *
 * someclass->MyFunction = &replaceme;
 *
 * After this point, calls to someclass->MyFunction will call the new code in your
 * replacement functor.
 *
 * This is a very powerful feature which should be considered 'advanced' and not for
 * beginners. If you do not understand these templates, STAY AWAY from playing with
 * this until you do, as if you get this wrong, this can generate some pretty long
 * winded and confusing error messages at compile time.
 */

template <typename ReturnType> class CoreExport HandlerBase0
{
 public:
	virtual ReturnType Call() = 0;
	virtual ~HandlerBase0() { }
};

template <typename ReturnType, typename Param1> class CoreExport HandlerBase1
{
 public:
	virtual ReturnType Call(Param1) = 0;
	virtual ~HandlerBase1() { }
};

template <typename ReturnType, typename Param1, typename Param2> class CoreExport HandlerBase2
{
 public:
	virtual ReturnType Call(Param1, Param2) = 0;
	virtual ~HandlerBase2() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3> class CoreExport HandlerBase3
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3) = 0;
	virtual ~HandlerBase3() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4> class CoreExport HandlerBase4
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3, Param4) = 0;
	virtual ~HandlerBase4() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5> class CoreExport HandlerBase5
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3, Param4, Param5) = 0;
	virtual ~HandlerBase5() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6> class CoreExport HandlerBase6
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3, Param4, Param5, Param6) = 0;
	virtual ~HandlerBase6() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7> class CoreExport HandlerBase7
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3, Param4, Param5, Param6, Param7) = 0;
	virtual ~HandlerBase7() { }
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7, typename Param8> class CoreExport HandlerBase8
{
 public:
	virtual ReturnType Call(Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8) = 0;
	virtual ~HandlerBase8() { }
};

template <typename HandlerType> class CoreExport caller
{
 public:
	HandlerType* target;

	caller(HandlerType* initial)
	: target(initial)
	{ }

	virtual ~caller() { }

	caller& operator=(HandlerType* newtarget)
	{
		target = newtarget;
		return *this;
	}
};

template <typename ReturnType> class CoreExport caller0 : public caller< HandlerBase0<ReturnType> >
{
 public:
	caller0(HandlerBase0<ReturnType>* initial)
	: caller< HandlerBase0<ReturnType> >::caller(initial)
	{ }

	virtual ReturnType operator() ()
	{
		return this->target->Call();
	}
};

template <typename ReturnType, typename Param1> class CoreExport caller1 : public caller< HandlerBase1<ReturnType, Param1> >
{
 public:
	caller1(HandlerBase1<ReturnType, Param1>* initial)
	: caller< HandlerBase1<ReturnType, Param1> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1)
	{
		return this->target->Call(param1);
	}
};

template <typename ReturnType, typename Param1, typename Param2> class CoreExport caller2 : public caller< HandlerBase2<ReturnType, Param1, Param2> >
{
 public:
	caller2(HandlerBase2<ReturnType, Param1, Param2>* initial)
	: caller< HandlerBase2<ReturnType, Param1, Param2> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2)
	{
		return this->target->Call(param1, param2);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3> class CoreExport caller3 : public caller< HandlerBase3<ReturnType, Param1, Param2, Param3> >
{
 public:
	caller3(HandlerBase3<ReturnType, Param1, Param2, Param3>* initial)
	: caller< HandlerBase3<ReturnType, Param1, Param2, Param3> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3)
	{
		return this->target->Call(param1, param2, param3);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4> class CoreExport caller4 : public caller< HandlerBase4<ReturnType, Param1, Param2, Param3, Param4> >
{
 public:
	caller4(HandlerBase4<ReturnType, Param1, Param2, Param3, Param4>* initial)
	: caller< HandlerBase4<ReturnType, Param1, Param2, Param3, Param4> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3, Param4 param4)
	{
		return this->target->Call(param1, param2, param3, param4);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5> class CoreExport caller5 : public caller< HandlerBase5<ReturnType, Param1, Param2, Param3, Param4, Param5> >
{
 public:
	caller5(HandlerBase5<ReturnType, Param1, Param2, Param3, Param4, Param5>* initial)
	: caller< HandlerBase5<ReturnType, Param1, Param2, Param3, Param4, Param5> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5)
	{
		return this->target->Call(param1, param2, param3, param4, param5);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6> class CoreExport caller6 : public caller< HandlerBase6<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6> >
{
 public:
	caller6(HandlerBase6<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6>* initial)
	: caller< HandlerBase6<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5, Param6 param6)
	{
		return this->target->Call(param1, param2, param3, param4, param5, param6);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7> class CoreExport caller7 : public caller< HandlerBase7<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7> >
{
 public:
	caller7(HandlerBase7<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7>* initial)
	: caller< HandlerBase7<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5, Param6 param6, Param7 param7)
	{
		return this->target->Call(param1, param2, param3, param4, param5, param6, param7);
	}
};

template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7, typename Param8> class CoreExport caller8 : public caller< HandlerBase8<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8> >
{
 public:
	caller8(HandlerBase8<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8>* initial)
	: caller< HandlerBase8<ReturnType, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8> >(initial)
	{ }

	virtual ReturnType operator() (Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5, Param6 param6, Param7 param7, Param8 param8)
	{
		return this->target->Call(param1, param2, param3, param4, param5, param6, param7, param8);
	}
};

/** These shorthand macros are used to define a functor class which only implements Call(). Most functors are like this.
 * If you want something more complex, define them by hand.
 *
 * The first parameter to each macro is the class name to define, the second parameter is the return value of Call().
 * The following parameters are the parameter types for Call(), and again, the macro is numbered to match the number of
 * parameters, to prevent mistakes.
 */

#define DEFINE_HANDLER0(NAME, RETURN) \
	class CoreExport NAME : public HandlerBase0<RETURN> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(); };

#define DEFINE_HANDLER1(NAME, RETURN, V1) \
	class CoreExport NAME : public HandlerBase1<RETURN, V1> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1); };

#define DEFINE_HANDLER2(NAME, RETURN, V1, V2) \
	class CoreExport NAME : public HandlerBase2<RETURN, V1, V2> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2); };

#define DEFINE_HANDLER3(NAME, RETURN, V1, V2, V3) \
	class CoreExport NAME : public HandlerBase3<RETURN, V1, V2, V3> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3); };

#define DEFINE_HANDLER4(NAME, RETURN, V1, V2, V3, V4) \
	class CoreExport NAME : public HandlerBase4<RETURN, V1, V2, V3, V4> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3, V4); };

#define DEFINE_HANDLER5(NAME, RETURN, V1, V2, V3, V4, V5) \
	class CoreExport NAME : public HandlerBase5<RETURN, V1, V2, V3, V4, V5> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3, V4, V5); };

#define DEFINE_HANDLER6(NAME, RETURN, V1, V2, V3, V4, V5, V6) \
	class CoreExport NAME : public HandlerBase6<RETURN, V1, V2, V3, V4, V5, V6> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3, V4, V5, V6); };

#define DEFINE_HANDLER7(NAME, RETURN, V1, V2, V3, V4, V5, V6, V7) \
	class CoreExport NAME : public HandlerBase7<RETURN, V1, V2, V3, V4, V5, V6, V7> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3, V4, V5, V6, V7); };

#define DEFINE_HANDLER8(NAME, RETURN, V1, V2, V3, V4, V5, V6, V7, V8) \
	class CoreExport NAME : public HandlerBase8<RETURN, V1, V2, V3, V4, V5, V6, V7, V8> { InspIRCd* Server; public: NAME(InspIRCd* Srv) : Server(Srv) { } virtual ~NAME() { } virtual RETURN Call(V1, V2, V3, V4, V5, V6, V7, V8); };

#endif


#ifndef FSM_H_
#define FSM_H_

#include "typedefs.h"

#define FSM_SIG_ENTRY      0
#define FSM_SIG_EXIT       1

typedef unsigned int state_t;
typedef unsigned int signal_t;
typedef struct parser parser_t;
typedef struct fsm fsm_t;

typedef void (*statetranfunc_t)(parser_t * me,signal_t sig);
typedef void (*sigupdatefunc_t)(void);
struct fsm
{
   statetranfunc_t statetranfun;
};
struct parser
{
  fsm_t tranfun;
  state_t currentstate;
  state_t prestate;
};


#define FsmDispatch(me,sig)  (*((me)->tranfun).statetranfun)((me),sig)
#define FsmInit(me)          (*((me)->tranfun).statetranfun)((me),0)
#define TRAN(me,target)      (((me)->tranfun).statetranfun=(statetranfunc_t)(target))

#define TRAN_EE(me, target) do{\
    (*((me)->tranfun).statetranfun)((me),FSM_SIG_EXIT);\
    ((me)->tranfun).statetranfun=(statetranfunc_t)(target);\
    (*((me)->tranfun).statetranfun)((me),FSM_SIG_ENTRY);\
}while(0)

#endif

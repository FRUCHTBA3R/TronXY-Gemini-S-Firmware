#ifndef Y_EVENT_HPP
#define	Y_EVENT_HPP
#include "../yCommon.h"
#define	EVENT_MAX_NUM	16	//Supports up to 16 routes and up to 32 events per route
#define EVENT_MAX_EVT   32

typedef uint8_t (*yEventFun)(void);
class yEvent
{
private:
	uint8_t number;
	uint8_t paral[EVENT_MAX_NUM];
	uint8_t head[EVENT_MAX_NUM];
	uint8_t tail[EVENT_MAX_NUM];
	uint32_t _evt[EVENT_MAX_NUM];
	uint8_t (*funs[EVENT_MAX_NUM][EVENT_MAX_EVT])(void);
public:
	yEvent();
	/*******************************************************************************
	* Function name  	:setEvt
	* describe     		:Open an event on the target task
	* parameter   		:taskIndex task number, the task must be registered first
						:evt event number, cannot be greater than 31
						:evtFun event function, if it is not nullptr, it will update the registration or the function of the last setEvt
	* return      		:Returns true if enabled successfully, otherwise false
	* Writer	    	:YSZ
	* date of writing  	:2020-02-20
	*******************************************************************************/
	uint8_t setEvt(uint8_t taskIndex, uint8_t evt, uint8_t (*const evtFun)(void) = nullptr);

	/*******************************************************************************
	* Function name    	:deleteEvt
	* describe      	:Delete an event on the target task
	* parameter      	:taskIndex task number
						:evt event number, cannot be greater than 31
	* return      		:Return true if enabled successfully, otherwise false
	* Writer	    	:YSZ
	* date of writing  	:2022-09-06
	*******************************************************************************/
	uint8_t deleteEvt(uint8_t taskIndex, uint8_t evt);
	inline uint8_t hasEvt(uint8_t taskIndex, uint8_t evt)
	{
		return (_evt[taskIndex] & (1UL << evt));
	}
	yEventFun getEvtFun(uint8_t taskIndex, uint8_t evt);
	
	/*******************************************************************************
	* Function name    	:addEvt
	* describe      	:Add an event to the task. The event does not need to be registered first.
	* parameter      	:taskIndex task number
						:evtFun event function
	* return      		:If it is a parallel task, the returnfalse addition fails.
	* Writer    		:YSZ
	* date of writing  	:2022-09-05
	*******************************************************************************/
	uint8_t addEvt(uint8_t taskIndex, uint8_t (*const evtFun)(void) = nullptr);
	uint8_t getNextEvt(uint8_t taskIndex);//获取下一个可被加入事件的编号

	/*******************************************************************************
	* Function name	    :registerTask
	* describe      	:Task registration
	* parameter      	:index - the number of the registered task, which can be freely defined. Note that different tasks must be assigned different numbers, and the maximum cannot exceed EVENT_MAX_NUM - 1
						:funLen - the number of functions corresponding to all events that need to be executed by the task, cannot be greater than EVENT_MAX_EVT - 1
						:fun - a collection of functions corresponding to all events that need to be executed by the task
						:Parallel - Whether all events of the task are executed in parallel, true parallel, false priority execution, the smaller the event number, the higher the priority
	* return      		:Return true if registration is successful, otherwise false
	* Writer	    	:YSZ
	* date of writing  	:2020-02-20
	*******************************************************************************/
	uint8_t registerTask(uint8_t index, uint8_t funLen, uint8_t (*const fun[])(void), uint8_t parallel = false);
	/*******************************************************************************
	* Function name    	:execute
	* describe      	:Continuous task event loop
	* parameter      	:-
	* return      		:-
	* Writer	    	:YSZ
	* date of writing  	:2020-02-20
	*******************************************************************************/
	void execute();
};

#endif

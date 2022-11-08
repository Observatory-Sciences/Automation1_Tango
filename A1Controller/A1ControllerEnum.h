#ifndef A1ControllerEnum_H
#define A1ControllerEnum_H

namespace A1Controller_ns
{
    enum _Automation1TaskStatusEnum {
	_UNAVAILABLE,
	_INACTIVE,
	_IDLE,
	_PROGRAMREADY,
	_PROGRAMRUNNING,
	_PROGRAMFEEDHOLD,
	_PROGRAMPAUSED,
	_PROGRAMCOMPLETE,
	_ERROR,
	_QUEUERUNNING,
	_QUEUEPAUSED,
} ;
typedef _Automation1TaskStatusEnum Automation1TaskStatusEnum;
}

#endif
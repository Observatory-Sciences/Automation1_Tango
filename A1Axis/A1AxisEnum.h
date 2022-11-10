
#ifndef A1AxisEnum_H
#define A1AxisEnum_H

namespace A1Axis_ns
{

enum _HomeTypeEnum {
    _ASYNCHRONOUS,
    _SYNCHRONOUS,
} ;
typedef _HomeTypeEnum HomeTypeEnum;

enum _MoveTypeEnum {
    _ABSOLUTEMOVE,
    _INCREMENTALMOVE,
    _LINEARMOVE,
    _RAPIDMOVE,
} ;
typedef _MoveTypeEnum MoveTypeEnum;

enum _RampTypeEnum {
    _LINEAR,
    _S_CURVE,
    _SINE,
} ;
typedef _RampTypeEnum RampTypeEnum;

enum _RampModeEnum {
    _RATE,
    _TIME,
} ;
typedef _RampModeEnum RampModeEnum;

}

#endif // A1AxisEnum_H

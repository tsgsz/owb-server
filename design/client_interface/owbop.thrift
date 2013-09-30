namespace cpp owb
namespace java owb
namespace cocoa owb

struct OwbPoint {  
1: required i32 x;
2: required i32 y;
}

enum OwbDrawOpType {
    LINE = 0,
    ELLIPSE = 1,
    RECTANGE = 2,
    POINT = 3
}

struct OwbDrawOp {
1: required bool mid_op;
2: required OwbDrawOpType type;
3: required OwbPoint start_point;
4: optional OwbPoint end_point;
5: required i32 thickness;
6: required i32 color;
7: optional bool is_fill;
8: optional bool alpha;
//for eraser and point: this means is start or not
//for other shape: this means is end or not
9: optional bool status;
}

enum OwbOpType {
    DRAW = 0,
    SAVE = 1,
    RELOAD = 2,
}

struct OwbSaveOp {
1: required string sponsor;
2: required string time;
3: optional string notes;
}

struct OwbReloadOp {
1: required string sponsor;
2: required string time;
3: required i32 reload_point;
}

struct OwbOp {
1: required i32 opid;
2: required OwbOpType type;
3: optional OwbDrawOp draw_op;
4: optional OwbSaveOp save_op;
5: optional OwbReloadOp reload_op;
}

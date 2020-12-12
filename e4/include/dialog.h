#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "map.h"
/// 负责UI层的互动
class Dialog
{
    Map map;
    /// 查询公交线路
    void query_bus();
    /// 查询两点间的全部路径
    void query_path();
    /// 查询经过车站的公交线路
    void query_stop();
public:
    Dialog(const char* file_name);
    Dialog(const Map& map);
    void begin_dialog();
};

#endif // _DIALOG_H_
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdio>
#include "CmdOption.h"

// 高级用法示例源码
// 延迟子绑定
#include "DelayBind.h"
// 绑定仿函数
#include "BindObj.h"
// 命令忽略大小写
#include "CaseIgnoreBind.h"

class foo;
foo* g_test = NULL;

class foo {
public:
    void print_t(copt::callback_param par, std::string& str)
    {
        printf("sizeof(float) => %d\n", static_cast<int>(sizeof(float)));
        printf("sizeof(double) => %d\n", static_cast<int>(sizeof(double)));
        printf("sizeof(long double) => %d\n", static_cast<int>(sizeof(long double)));

        str = "Hello World!";
    }

    void print(copt::callback_param par)
    {
        puts("bt func:");
        int len = static_cast<int>(par.GetParamsNumber());
        for (int i = 0; i < len; ++i)
        {
            puts(par[i]->AsString());
        }

        g_test = this;
    }

    void print_t2(copt::callback_param par, int i)
    {
        printf("Mem Fun B2 Params Num: %d, i => %d\n", static_cast<int>(par.GetParamsNumber()), i);
    }

    void print_t3(copt::callback_param par, int i, double d)
    {
        printf("Mem Fun B3 Params Num: %d, i => %d, d => %lf\n", static_cast<int>(par.GetParamsNumber()), i, d);
    }
};

class foo2: public foo {
    void print(copt::callback_param par, std::string& str)
    {
        str = "Hello World! - child";
    }
};

void print(copt::callback_param par, std::string* str)
{
    printf("sizeof(short) => %d\n", static_cast<int>(sizeof(short)));
    printf("sizeof(int) => %d\n", static_cast<int>(sizeof(int)));
    printf("sizeof(long) => %d\n", static_cast<int>(sizeof(long)));

    (*str) = par.Get("par1")->AsString();
}

void print(copt::callback_param par)
{
    puts("do nothing! - free func without parameter\n");
}

void print2(copt::callback_param par, double d)
{
    printf("Free Fun B2 Params Num: %d, d => %lf\n", static_cast<int>(par.GetParamsNumber()), d);
}

void print3(copt::callback_param par, double d, int i)
{
    printf("Free Fun B3 Params Num: %d, i => %d, d => %lf\n", static_cast<int>(par.GetParamsNumber()), i, d);
}


int complexBindFunc(copt::callback_param par, int i){
    printf("%d\n", i);
    return 0;
}

void onError(copt::callback_param par) {
    puts("Error:");
    printf("Error Command: %s, Error Message: %s\n", par.Get("@Cmd")->AsString(), par.Get("@ErrorMsg")->AsString());
}

int main() {
    copt::CmdOption::ptr_type co = copt::CmdOption::Create();
    copt::CmdOption::ptr_type cco = copt::CmdOption::Create();

    foo f, *pf = new foo2();
    std::string str;
    
    // 绑定错误处理函数
    co->BindCmd("@OnError", onError);

    // 带参数类函数绑定（参数为引用）
    co->BindCmd("-bt1, --bind_class_func_param", &foo::print_t, pf, std::ref(str))->SetHelpMsg("-bt1, --bind_class_func_param    带参数类绑定");
    // 带参数类函数绑定（多个参数）
    co->BindCmd("-bt2, --bind_class_func_param2", &foo::print_t2, pf, 1011);
    co->BindCmd("-bt3, --bind_class_func_param3", &foo::print_t3, pf, 1013, 10.13);
    // 无参数类函数绑定
    co->BindCmd("-bt, --bind_class_func", &foo::print, std::ref(f))->SetHelpMsg("-bt, --bind_class_func    无参数类绑定");
    // 带参数普通函数绑定(自动类型推断)
    cco->BindCmd("-bf1, --bind_func_param1", (void (*)(copt::callback_param, std::string*))print, &str)->SetHelpMsg("-bf1, --bind_func_param    带参数函数绑定");

    cco->BindCmd("-bf2, --bind_func_param2", print2, 20.11);
    cco->BindCmd("-bf3, --bind_func_param3", print3, 20.11, 2013);

    // 无参数普通函数绑定
    cco->BindCmd("-bf, --bind_func", (void(*)(copt::callback_param))print)->SetHelpMsg("-bf, --bind_func    无参数函数绑定");
    // 复杂多指令绑定
    co->BindCmd("wo  ;le  , ge, cha,de", complexBindFunc, 100);
    // 绑定子绑定对象
    co->BindChildCmd("-c, --child", cco)->SetHelpMsg("-c, --child    ");
    // 绑定多指令的默认执行函数
    co->BindCmd("@OnDefault", (void(*)(copt::callback_param))print);

    // 单指令启动测试
    co->Start("-c lala def -bf1 par1 par2 par3 -bf2 -bf3 fp1");
    co->Start("-bt btpar1 \"test end of line\\r\\n\tanother line\"-bt1 with one param --bind_class_func_param2 p1 p2 p3 -bt3 p4");
    printf("成员函数绑定传入对象引用包装测试: %s\n", (g_test == &f) ? "通过" : "失败！！！！！！！！！！！");

    // 多指令启动测试
    const char* strCmds[] = {"path", "par1", "par2", "wo", "le", "ge", "cha"};
    co->Start(7, strCmds);
    puts(str.c_str());

    // 错误处理测试
    co->Start("do_nothing");
    puts("绑定测试完毕\n");

    // 添加帮助信息测试
    co->GetBindedCmd("wo")->AddHelpMsg("wo, le, ge, cha, de")->AddHelpMsg("   复杂指令绑定");
    std::shared_ptr<std::vector<const char*> > cmds = co->GetCmdNames();
    printf("CMDS: ");
    for (unsigned int i = 0; i < cmds->size(); ++i) {
        printf(" %s;", (*cmds)[i]);
    }
    puts("");
    co->BindHelpCmd("h, help")->SetHelpMsg("h, help      帮助信息");
    co->Start("help");
    puts("默认帮助函数测试完成\n");


    // 高级用法 例程函数

    // 延迟绑定初始化
    delay_bind();

    // 绑定函数对象
    bind_obj_init();

    // 命令忽略大小写
    bind_ci_cmd_init();

    // 回收资源
    delete pf;

    return 0;
}

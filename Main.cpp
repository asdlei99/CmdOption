#include <iostream>
#include <cstdio>
#include "CmdOption.h"

// �߼��÷�ʾ��Դ��
// �ӳ��Ӱ�
#include "DelayBind.h"
// �󶨷º���
#include "BindObj.h"
// ������Դ�Сд
#include "CaseIgnoreBind.h"

class foo {
public:
    void print_t(copt::callback_param par, std::string& str)
    {
        printf("sizeof(float) => %d\n", sizeof(float));
        printf("sizeof(double) => %d\n", sizeof(double));
        printf("sizeof(long double) => %d\n", sizeof(long double));

        str = "Hello World!";
    }

    void print(copt::callback_param par)
    {
        puts("do nothing!\n");
    }

    void print_t2(copt::callback_param par, int i)
    {
        printf("Mem Fun B2 Params Num: %d, i => %d\n", par.GetParamsNumber(), i);
    }

    void print_t3(copt::callback_param par, int i, double d)
    {
        printf("Mem Fun B3 Params Num: %d, i => %d, d => %lf\n", par.GetParamsNumber(), i, d);
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
    printf("sizeof(short) => %d\n", sizeof(short));
    printf("sizeof(int) => %d\n", sizeof(int));
    printf("sizeof(long) => %d\n", sizeof(long));

    (*str) = par.Get("par1")->AsString();
}

void print(copt::callback_param par)
{
    puts("do nothing! - free func without parameter\n");
}

void print2(copt::callback_param par, double d)
{
    printf("Free Fun B2 Params Num: %d, d => %lf\n", par.GetParamsNumber(), d);
}

void print3(copt::callback_param par, double d, int i)
{
    printf("Free Fun B3 Params Num: %d, i => %d, d => %lf\n", par.GetParamsNumber(), i, d);
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

    copt::CmdOption co, cco;
    
    foo f, *pf = new foo2();
    std::string str;
    
    // �󶨴�������
    co.BindCmd("@OnError", onError);

    // �������ຯ���󶨣�����Ϊ���ã�
    co.BindCmd("-bt1, --bind_class_func_param", &foo::print_t, *pf, std::ref(str))->SetHelpMsg("-bt1, --bind_class_func_param    ���������");
    // �������ຯ���󶨣����������
    co.BindCmd("-bt2, --bind_class_func_param2", &foo::print_t2, *pf, 1011);
    co.BindCmd("-bt3, --bind_class_func_param3", &foo::print_t3, *pf, 1013, 10.13);
    // �޲����ຯ����
    co.BindCmd("-bt, --bind_class_func", &foo::print, f)->SetHelpMsg("-bt, --bind_class_func    �޲������");
    // ��������ͨ������(�Զ������ƶ�)
    cco.BindCmd("-bf1, --bind_func_param1", print, &str)->SetHelpMsg("-bf1, --bind_func_param    ������������");
    cco.BindCmd("-bf2, --bind_func_param2", print2, 20.11);
    cco.BindCmd("-bf3, --bind_func_param3", print3, 20.11, 2013);

    // �޲�����ͨ������
    cco.BindCmd("-bf, --bind_func", print)->SetHelpMsg("-bf, --bind_func    �޲���������");
    // ���Ӷ�ָ���
    co.BindCmd("wo  ;le  , ge, cha,de", complexBindFunc, 100);
    // ���Ӱ󶨶���
    co.BindChildCmd("-c, --child", cco)->SetHelpMsg("-c, --child    ");
    // �󶨶�ָ���Ĭ��ִ�к���
    co.BindCmd("@OnDefault", print);

    // ��ָ����������
    co.Start("-c lala def -bf1 par1 par2 par3 -bf2 -bf3 fp1");
    co.Start("-bt btpar1 -bt1 with one param --bind_class_func_param2 p1 p2 p3 -bt3 p4");

    // ��ָ����������
    const char* strCmds[] = {"path", "par1", "par2", "wo", "le", "ge", "cha"};
    co.Start(7, strCmds);
    puts(str.c_str());

    // ���������
    co.Start("do_nothing");
    puts("�󶨲������\n");

    // ��Ӱ�����Ϣ����
    co.GetBindedCmd("wo")->AddHelpMsg("wo, le, ge, cha, de")->AddHelpMsg("   ����ָ���");
    std::shared_ptr<std::vector<const char*> > cmds = co.GetCmdNames();
    printf("CMDS: ");
    for (unsigned int i = 0; i < cmds->size(); ++i) {
        printf(" %s;", (*cmds)[i]);
    }
    puts("");
    co.BindHelpCmd("h, help")->SetHelpMsg("h, help      ������Ϣ");
    co.Start("help");
    puts("Ĭ�ϰ��������������\n");


    // �߼��÷� ���̺���

    // �ӳٰ󶨳�ʼ��
    delay_bind();

    // �󶨺�������
    bind_obj_init();

    // ������Դ�Сд
    bind_ci_cmd_init();

    // ������Դ
    delete pf;

    return 0;
}

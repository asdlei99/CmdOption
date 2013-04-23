#ifndef _TEST_DELAYBIND_H_
#define _TEST_DELAYBIND_H_


#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <iostream>
#include <cstdio>
#include "CmdOption.h"

// �ӳٰ󶨳�ʼ��
bool delay_print(copt::callback_param par) {
    if (par.GetParamsNumber() > 0)
        puts(par[0]->AsString());
    return false;
}

void delay_init(copt::callback_param par, copt::CmdOption* stChild) {
    printf("Delay Init Params Num: %d\n", par.GetParamsNumber());
    stChild->BindCmd("-p, --print", delay_print);
}

void delay_bind() {
    puts("�ӳٳ�ʼ���Ӱ�");
    copt::CmdOption f;
    std::shared_ptr<copt::CmdOption> pc = std::shared_ptr<copt::CmdOption>(new copt::CmdOption());
    pc->BindCmd("@OnCallFunc", delay_init, pc.get());   // ���ó�ʼ������
    // ע�����ﲻ�ܴ���*pc
    // ��Ϊ����������ã���CmdOption�ṹ�ᱻ���ƣ�Ȼ����Ϊf������������벢�ӳٰ󶨵���pc��ָ��
    f.BindChildCmd("-c, --child", pc);                       

    f.Start("-c a b c -p \"Delay Init Child Option With \\\"delay_print\\\".\"");

    puts("�ӳٳ�ʼ���Ӱ� �������\n");
}

#endif

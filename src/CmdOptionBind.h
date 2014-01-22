#ifndef _CMDOPTIONBIND_H_
#define _CMDOPTIONBIND_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/*
 * CmdOptionBind.h
 *
 *  Created on: 2011-12-29
 *      Author: OWenT
 *
 * Ӧ�ó��������
 * ����ģ�壨�������а󶨵ĺ��������Ա������
 */

#include "CmdOptionBindT_CC.h"
#include "CmdOptionBindT_MF_CC.h"

namespace copt
{
    // ��׼ָ�����(�޷���ֵ������Ϊѡ���ӳ���)
    // void function_name (CmdOptionList&, [����]); // ����������ѡ
    // void function_name (callback_param, [����]); // ����������ѡ

    enum CmdOptionChar 
    {
        SPLITCHAR = 0x0001,     // (��һλ)�ָ���
        STRINGSYM = 0x0002,     // (�ڶ�λ)�ַ������շ�
        TRANSLATE = 0x0004,     // (����λ)ת���ַ�
        CMDSPLIT  = 0x0008,     // (����λ)ָ��ָ���
    };
}
#endif /* _CMDOPTIONBIND_H_ */

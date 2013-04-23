#ifndef _CMDOPTIONLIST_H_
#define _CMDOPTIONLIST_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/*
 * CmdOptionList.h
 *
 *  Created on: 2011-12-29
 *      Author: owentou(ŷ���)
 *
 * Ӧ�ó��������
 *
 */

#include <string>
#include <map>
#include <vector>

#include "smart_ptr.h"
#include "CmdOptionValue.h"

namespace copt
{
    class CmdOptionList
    {
    protected:
        std::shared_ptr<std::map<std::string, std::shared_ptr<CmdOptionValue> > > m_pKeyValue;
        std::vector<std::shared_ptr<CmdOptionValue> > m_stKeys;

        // ��ʼ��Key-Valueӳ�䣨���ڵ�һ�ε���Get(key)ʱ���ã�
        void initKeyValueMap();

    public:
        // ���Ͷ���
        typedef std::shared_ptr<CmdOptionValue> value_type;     // ֵ����
        typedef std::vector<value_type>::size_type size_type;   // ��С����

        // ���캯��
        CmdOptionList();
        CmdOptionList(int argv, const char* argc[]);
        CmdOptionList(const std::vector<std::string>& stCmds);

        // ����ѡ��
        void Add(const char* strParam);

        // ɾ��ȫ��ѡ��
        void Clear();

        // ���ݼ�ֵ��ȡѡ��ָ�룬��������ڷ���Ĭ��ֵ
        value_type Get(std::string strKey, const char* strDefault);

        // ���ݼ�ֵ��ȡѡ��ָ�룬��������ڷ��ؿ�ָ��
        value_type Get(std::string strKey);

        // �����±��ȡѡ��ָ�룬��������ڻ��������ʱ����
        value_type Get(int iIndex) const;

        // ���������أ����ܺ�����һ��
        value_type operator[](int iIndex) const;

        // ��ȡ��������
        size_type GetParamsNumber() const;

        // ����Key-Valueӳ���
        // # �ڵ�һ�ε���Get(�ַ���[, Ĭ��ֵ])��Ὠ��ӳ���
        // # �����֮��Add�˲�����û�е��ô˺�������ӳ���
        // # �µı������������ӳ���
        void ResetKeyValueMap();
    };
}

#endif /* _CMDOPTIONLIST_H_ */

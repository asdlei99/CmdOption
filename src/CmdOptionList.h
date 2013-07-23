#ifndef _CMDOPTIONLIST_H_
#define _CMDOPTIONLIST_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/*
 * CmdOptionList.h
 *
 *  Created on: 2011-12-29
 *      Author: OWenT
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
    class CmdOptionList;
    typedef CmdOptionList& callback_param;

    namespace binder
    {
        struct unspecified {};

        // �����ӿ�
        class CmdOptionBindBase: public std::enable_shared_from_this<CmdOptionBindBase>
        {
        protected:
            std::string m_strHelpMsg;
            virtual ~CmdOptionBindBase(){}
        public:
            // �����������
            typedef callback_param param_type;

            virtual void operator()(callback_param arg) = 0;

            // ��ȡ�����İ�����Ϣ
            virtual std::string GetHelpMsg(const char* strPre = "")
            {
                return strPre + m_strHelpMsg;
            }

            // ���ð����İ�����Ϣ
            virtual std::shared_ptr<CmdOptionBindBase> SetHelpMsg(const char* strHelp)
            {
                m_strHelpMsg = strHelp;
                return shared_from_this();
            }

            // ���Ӱ����İ�����Ϣ
            virtual std::shared_ptr<CmdOptionBindBase> AddHelpMsg(const char* strHelp)
            {
                m_strHelpMsg += strHelp;
                return shared_from_this();
            }
        };
    }


    class CmdOptionList
    {
    public:
        // ���Ͷ���
        typedef std::vector< std::pair<std::string, std::shared_ptr<binder::CmdOptionBindBase> > > cmd_array_type;   // ��С����
        typedef std::shared_ptr<CmdOptionValue> value_type;     // ֵ����
        typedef std::vector<value_type>::size_type size_type;   // ��С����

    protected:
        
        std::shared_ptr<std::map<std::string, std::shared_ptr<CmdOptionValue> > > m_pKeyValue;
        std::vector<std::shared_ptr<CmdOptionValue> > m_stKeys;
        cmd_array_type m_stCmdArray;

        // ��ʼ��Key-Valueӳ�䣨���ڵ�һ�ε���Get(key)ʱ���ã�
        void initKeyValueMap();

    public:

        // ���캯��
        CmdOptionList();
        CmdOptionList(int argv, const char* argc[]);
        CmdOptionList(const std::vector<std::string>& stCmds);

        // ����ѡ��
        void Add(const char* strParam);

        // ɾ��ȫ��ѡ��
        void Clear();

        // ��ȡָ�
        void LoadCmdArray(const cmd_array_type& stCmds);

        // ���ָ��
        void AppendCmd(const char* strCmd, std::shared_ptr<binder::CmdOptionBindBase> stBase);

        // �Ƴ�ĩβָ��
        void PopCmd();

        const cmd_array_type& GetCmdArray() const;

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

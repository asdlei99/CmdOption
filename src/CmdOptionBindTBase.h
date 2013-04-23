#ifndef _CMDOPTIONBINDTBASE_H_
#define _CMDOPTIONBINDTBASE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/*
 * CmdOptionBindTBase.h
 *
 *  Created on: 2012-01-18
 *      Author: owentou(ŷ���)
 *
 * �������༰��������
 */

#include <string>

#include "CmdOptionList.h"

namespace copt
{
    // ��׼ָ�������������
    typedef CmdOptionList& callback_param;
    // ��׼ָ�����(�޷���ֵ������Ϊѡ���ӳ���)
    // void function_name (CmdOptionList&, [����]); // ����������ѡ
    // void function_name (callback_param, [����]); // ����������ѡ

    // ��������
    namespace binder {
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

        // �����������ṹ����
        template<class _R, class _F, class _L> 
        class CmdOptionBindT : public CmdOptionBindBase
        {
        protected:
            _F m_fFuncObj;      // �����ṹ
            _L m_stParamList;   // �����б�ṹ

        public:
            typedef CmdOptionBindT this_type;

            CmdOptionBindT(_F f, _L l): m_fFuncObj(f), m_stParamList(l) {}

            void operator()(callback_param args)
            {
                m_stParamList(m_fFuncObj, args, 0);
            }                      
        };

    }
}
#endif /* _CMDOPTIONBIND_H_ */

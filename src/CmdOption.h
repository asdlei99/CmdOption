#ifndef _CMDOPTION_H_
#define _CMDOPTION_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/**
 * CmdOptionBind<TCmdStr>.h
 * 
 *  Version: 1.3.2
 *  Created on: 2011-12-29
 *  Last edit : 2013-07-23
 *      Author: OWenT
 *
 * Ӧ�ó��������
 * �󶨹����C++ 11��ͬ��C++ 11�����Ա���Ǹ����࣬������������
 * ע��: ������󶨵�Ŀ�����⣬����Ĭ�ϵĺ����ƶϾ��Ǵ�ֵ��ʽ����
 *      ������ֵ�ĸ�����ִ��BindCmdʱ�������Ҫ������Ҫ��ʽָ����������
 *      ע��Ĭ���Ƶ���֧����ʽת��(����double��int��Ĭ���Ƶ�����float��short��long����Ҫָ����������)
 *      Ϊ�˸���Ч�����з���ֵ��ΪPDO���ͺ�ָ��/����ָ��
 *
 */

#include <exception>
#include <set>

#include <vector>
#include <map>


// �������
#include "CmdOptionBind.h"

#include "CmdOptionString.h"

#include "ref.h"

namespace copt
{
    // ��׼ָ�����(�޷���ֵ������Ϊѡ���ӳ���)
    // void function_name (CmdOptionList&, [����]); // ����������ѡ
    // void function_name (callback_param, [����]); // ����������ѡ

    // ֵ����
    typedef std::shared_ptr<copt::CmdOptionValue> value_type;


    /**
     * �������
     * �ڶ�����/�����б�(���ڴ����ڲ��¼�):
     *      @OnError    :  ����ʱ����
     *          @ErrorMsg   : @OnError �����Ĵ�������
     *
     *      @OnDefault  :  Ĭ��ִ�к���(����ִ����������ʱ�ĵ�һ��ָ��ǰ�Ĳ���)
     *                     ע�⣺�����һ����������ָ����@OnDefault�ᱻ����ղ���ִ��
     *
     *      @OnCallFunc :  ���������ת������ǰ(���������в�������������CmdOptionBind<TCmdStr>ִ��ʱ)
     *                     ���飺����������¼���Ӧ�������ٰ������������ָ������
     *                     [ע: ����Start����������Ӧ����¼�]
     */
    template<typename TCmdStr>
    class CmdOptionBind: public binder::CmdOptionBindBase
    {
    protected:
        static short m_strMapValue[256]; // ��¼��ͬ�ַ���ӳ���ϵ

        typedef std::map<TCmdStr, std::shared_ptr<binder::CmdOptionBindBase> > funmap_type;
        funmap_type m_stCallbackFuns; // ��¼�����ӳ�亯��

        /**
         * ִ������
         * @param strCmd ָ������
         * @param stParams ָ�����
         */
        void runCmd(const TCmdStr& strCmd, callback_param stParams) const
        {
            typename funmap_type::const_iterator stIter = m_stCallbackFuns.find(strCmd);

            if (stIter == m_stCallbackFuns.end())
            {
                // �ڶ���������Ҳ���ָ���
                if (strCmd == "@OnDefault")
                    return;

                stIter = m_stCallbackFuns.find("@OnError"); // ���Ҵ�������
                if (stIter != m_stCallbackFuns.end())
                {
                    // ĩβ�޲���Key����Value
                    if (stParams.GetParamsNumber() % 2)
                        stParams.Add("");

                    stParams.AppendCmd(strCmd.c_str(), std::shared_ptr<binder::CmdOptionBindBase>());
                    // ���󸽼�����(��������)
                    stParams.Add("@ErrorMsg");
                    stParams.Add("Command Invalid");
                    (*stIter->second)(stParams);
                }
                return;
            }
            stParams.AppendCmd(strCmd.c_str(), stIter->second);
            (*stIter->second)(stParams);
        }

        /**
         * ���ַ�����ȡһ���ֶΣ�����δ������ַ�����β��
         * @param strBegin Ҫ�������ַ�������ʼλ��
         * @param strVal �������
         * @return δ�������ֵĿ�ʼλ��
         */
        const char* getSegment(const char* strBegin, std::string& strVal) const
        {
            strVal.clear();
            char cFlag;  // �ַ��������ַ�

            // ȥ���ָ���ǰ׺
            while (*strBegin && (m_strMapValue[(int)*strBegin] & SPLITCHAR))
                ++ strBegin;

            while (*strBegin && !(m_strMapValue[(int)*strBegin] & SPLITCHAR))
            {
                if (!(m_strMapValue[(int)*strBegin] & STRINGSYM))
                {
                    strVal += *strBegin;
                    ++ strBegin;
                }
                else
                {
                    cFlag = *strBegin;
                    ++ strBegin;

                    while (*strBegin && *strBegin != cFlag)
                    {
                        if (m_strMapValue[(int)*strBegin] & TRANSLATE)
                        {
                            if (*(strBegin + 1))
                                ++ strBegin;
                        }

                        strVal += *strBegin;
                        ++ strBegin;
                    }

                    ++ strBegin;
                    break;  // �ַ����������������
                }
            }

            // ȥ���ָ�����׺
            while (*strBegin && (m_strMapValue[(int)*strBegin] & SPLITCHAR))
                ++ strBegin;
            return strBegin;
        }

        /**
         * ��ָ�����
         * @param strBegin Դ�ַ���
         * @return ������
         */
        std::vector<std::string> splitCmd(const char* strBegin) const
        {
            std::vector<std::string> stRet;
            for (const char* pBegin = strBegin; (*pBegin);)
            {
                std::string strCmd;
                // ȥ������ָ���ǰ׺
                while ((*pBegin) && (m_strMapValue[(int)*pBegin] & CMDSPLIT))
                    ++ pBegin;

                // ��������
                while ((*pBegin) && !(m_strMapValue[(int)*pBegin] & CMDSPLIT))
                {
                    strCmd.push_back(*pBegin);
                    ++ pBegin;
                }

                if (strCmd.size() > 0)
                    stRet.push_back(strCmd);
            }

            return stRet;
        }

        /**
         * Ĭ�ϰ�������
         */
        void onHelp(callback_param)
        {
            puts("Help:");
            puts(GetHelpMsg().c_str());
        }

    public:
        /**
         * ���캯��
         */
        CmdOptionBind()
        {
            // ����ѳ�ʼ��������
            if (m_strMapValue[(int)' '] & SPLITCHAR)
                return;

            // �ָ���
            m_strMapValue[(int)' '] = m_strMapValue[(int)'\t'] =
                m_strMapValue[(int)'\r'] = m_strMapValue[(int)'\n'] = SPLITCHAR;
            // �ַ������շ�
            m_strMapValue[(int)'\''] = m_strMapValue[(int)'\"'] = STRINGSYM;
            // ת���Ƿ�
            m_strMapValue[(int)'\\'] = TRANSLATE;
            // ָ��ָ���
            m_strMapValue[(int)' '] |= CMDSPLIT;
            m_strMapValue[(int)','] = m_strMapValue[(int)';'] = CMDSPLIT;
        }

        /**
         * ��ȡ�Ѱ󶨵�ָ���б�
         * @return ָ���б�ָ��
         */
        std::shared_ptr<std::vector<const char*> > GetCmdNames() const
        {
            typename funmap_type::const_iterator iter = m_stCallbackFuns.begin();
            std::shared_ptr<std::vector<const char*> > pRet = 
                std::shared_ptr<std::vector<const char*> >(new std::vector<const char*>());
            while (iter != m_stCallbackFuns.end())
            {
                pRet->push_back(iter->first.c_str());
                ++ iter;
            }
            return pRet;
        }

        /**
         * ��ȡ�Ѱ󶨵�ָ�����
         * @param strCmdName ָ������
         * @return �󶨵�ָ�����ָ��, δ�ҵ����ؿ�ָ��ָ��
         */
        std::shared_ptr<binder::CmdOptionBindBase> GetBindedCmd(const char* strCmdName) const
        {
            typename funmap_type::const_iterator iter = m_stCallbackFuns.find(strCmdName);
            if (iter == m_stCallbackFuns.end())
                return std::shared_ptr<binder::CmdOptionBindBase>();
            return iter->second;
        }

        /**
         * ����ָ��
         * ˵���� �ڵ�һ��ָ��ǰ�Ĳ�����������@OnDefault�¼�
         *     ������ͨ��Get[�����±�]��ȡ
         *     ��һ��ʹ��Get[�ַ���]ʱ����������ӳ���Get(0)Ϊkey��Get(1)Ϊvalue��Get(2)Ϊkey��Get(3)Ϊvalue����������
         *     ������һ��keyû��value��ִ��Get[key]�����ؿ�ָ��
         *     ע�⣺Get[ż���±�]��Ӧ������valueֵ��Get[�ַ���]���ص�ָ�빲������(������һ����һ��Ҳ��֮����)
         */

        /**
         * �����ѷ���ָ��(ʹ��CmdOptionList�洢������)
         * @param stArgs ���ݼ���
         * @param bSingleCmd �Ƿ�ǿ�Ƶ�ָ��, �����ǿ��, ��ָ�����Ʋ����ظ�
         */
        void Start(callback_param stArgs, bool bSingleCmd = false) const
        {
            int argv = stArgs.GetParamsNumber();
            CmdOptionList stCmdArgs;
            TCmdStr strCmd = bSingleCmd? "@OnError": "@OnDefault";
            for (int i = -1; i < argv; )
            {
                ++ i;
                stCmdArgs.Clear();
                stCmdArgs.LoadCmdArray(stArgs.GetCmdArray());

                for (; i < argv; ++ i)
                {
                    // �����еķ�ָ���ַ�����Ϊָ�����
                    if (m_stCallbackFuns.find(stArgs[i]->AsString()) == m_stCallbackFuns.end())
                    {
                        stCmdArgs.Add(stArgs[i]->AsString());
                    }
                    else
                    {
                        // ����ǵ�ָ������δ֪������ַ�@OnError������
                        if (bSingleCmd && stCmdArgs.GetParamsNumber() > 0)
                        {
                            runCmd(strCmd, stCmdArgs);
                            stCmdArgs.Clear();
                            stCmdArgs.LoadCmdArray(stArgs.GetCmdArray());
                        }

                        // ׷�����в�����ִ�е�ָ��
                        if (bSingleCmd)
                        {
                            strCmd = TCmdStr(stArgs[i]->AsCppString().c_str(), stArgs[i]->AsCppString().size());
                            for(++ i; i < argv; ++ i)
                                stCmdArgs.Add(stArgs[i]->AsString());
                        }
                        break;
                    }
                }

                runCmd(strCmd, stCmdArgs);
                if (i >= argv)
                    break;
                strCmd = TCmdStr(stArgs[i]->AsCppString().c_str(), stArgs[i]->AsCppString().size());
            }
        }

        /**
         * �����ѷ���ָ��(ʹ��char**�洢������)
         * @param argv ��������
         * @param argc �����б�
         * @param bSingleCmd �Ƿ�ǿ�Ƶ�ָ��, �����ǿ��, ��ָ�����Ʋ����ظ�
         */
        inline void Start(int argv, const char* argc[], bool bSingleCmd = false) const
        {
            CmdOptionList stList(argv, argc);
            Start(stList, bSingleCmd);
        }

        /**
         * �����ѷ���ָ��(ʹ��std::vector<std::string>�洢������)
         * @param stCmds ���ݼ���
         * @param bSingleCmd �Ƿ�ǿ�Ƶ�ָ��, �����ǿ��, ��ָ�����Ʋ����ظ�
         */
        inline void Start(const std::vector<std::string>& stCmds, bool bSingleCmd = false) const
        {
            CmdOptionList stList(stCmds);
            Start(stList, bSingleCmd);
        }
        
        /**
         * ����δ����ָ��(ʹ��const char*�洢�������ַ���)
         * @param strCmd ָ��
         * @param bSingleCmd �Ƿ�ǿ�Ƶ�ָ��, �����ǿ��, ��ָ�����Ʋ����ظ�
         */
        void Start(const char* strCmd, bool bSingleCmd = false) const
        {
            CmdOptionList stCmds;
            std::string strSeg;

            // ����ָ��
            while (*strCmd)
            {
                strCmd = getSegment(strCmd, strSeg);
                stCmds.Add(strSeg.c_str());
            }
        
            Start(stCmds, bSingleCmd);
        }

        /**
         * ����δ����ָ��(ʹ��const std::string&�洢�������ַ���)
         * @param strCmd ָ��
         * @param bSingleCmd �Ƿ�ǿ�Ƶ�ָ��, �����ǿ��, ��ָ�����Ʋ����ظ�
         */
        inline void Start(const std::string& strCmd, bool bSingleCmd = false) const
        {
            Start(strCmd.c_str(), bSingleCmd);
        }

        /**
         * ���ָ��
         * @param strCmd ָ������
         */
        inline void UnBindCmd(const std::string& strCmd)
        {
            TCmdStr strTCmd = TCmdStr(strCmd.c_str(), strCmd.size());
            m_stCallbackFuns.erase(strTCmd);
        }

        /**
         * ���ȫ��ָ��
         */
        inline void UnBindAllCmd()
        {
            m_stCallbackFuns.clear();
        }

        /**
         * ��Ĭ�ϰ�������
         * @param strHelpCmd ������������
         */
        inline std::shared_ptr< binder::CmdOptionBindT<void, void (CmdOptionBind<TCmdStr>::*)(callback_param), binder::CmdOptionBindMFParamList0<CmdOptionBind<TCmdStr> > > > 
            BindHelpCmd(const char* strHelpCmd)
        {
            return BindCmd(strHelpCmd, &CmdOptionBind<TCmdStr>::onHelp, *(this));
        }

        /**
         * ִ���ӽṹ
         */
        virtual void operator()(callback_param arg)
        {
            // ��Ӧ@OnCallFunc�¼�
            typename funmap_type::const_iterator iter = m_stCallbackFuns.find("@OnCallFunc");
            if (iter != m_stCallbackFuns.end())
                (*iter->second)(arg);
        
            // ����ִ��ָ�, �����ӽṹ��һ���ǵ�ָ��
            Start(arg, true);
        }

        /**
         * ��ȡ����ϵİ�����Ϣ
         * @param strPre ǰ׺
         */
        virtual std::string GetHelpMsg(const char* strPre = "")
        {
            std::set<typename funmap_type::mapped_type> stSet;
            std::string strHelpMsg;

            for (typename funmap_type::const_iterator iter = m_stCallbackFuns.begin(); iter != m_stCallbackFuns.end(); ++ iter)
            {
                // ɾ���ظ������ö���
                if (stSet.find(iter->second) != stSet.end())
                    continue;

                // ������������
                if ('@' == *iter->first.c_str())
                    continue;

                stSet.insert(iter->second);
                std::string strCmdHelp = iter->second->GetHelpMsg((strPre + m_strHelpMsg).c_str());

                if (strCmdHelp.size() > 0)
                {
                    if (strHelpMsg.size() > 0 && '\n' != *strHelpMsg.rbegin())
                        strHelpMsg += "\r\n"; 
                    strHelpMsg += strCmdHelp;
                }
            }
            return strHelpMsg;
        }

        /**
         * ����ָ����� (��ͬ����ᱻ����)
         * ֧����ͨ���������Ա����
         * ע�⣺���д������Ϊ���ã���ȷ����ִ��Startʱ�����δ���ͷţ��ر�ע��ָ��;ֲ�������
         * ע�⣺�����ĸ��Ʒ�����ִ��BindCmd����ʱ
         */

        /**
         * �����Ա�������޲�����
         * example:
         *      *.BindCmd(��������, ���Ա����ָ��, ��)
         *      *.BindCmd<����>(��������, ���Ա����ָ��, ��)
         *      *.BindCmd<����, ���Ա��������ֵ����>(��������, ���Ա����ָ��, ��)
         */
        template<typename _T, typename _R>  // ����(_T:��)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (_T::*)(callback_param), binder::CmdOptionBindMFParamList0<_T> > > 
            BindCmd(const std::string strCmd, _R (_T::*fn)(callback_param), _T& t)
        {
            typedef _R (_T::*F)(callback_param); 
            typedef binder::CmdOptionBindMFParamList0<_T> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(t)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex) 
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        /**
         * �����Ա����
         * BindCmd: �󶨲���[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ]
         * example:
         *      *.BindCmd(��������, ���Ա����ָ��, ��, ����)                                     // Ĭ�������ƶ��Ǵ�ֵ��������
         *      *.BindCmd<��������, ��������>(��������, ���Ա����ָ��, ��, ����)
         *      *.BindCmd<��������, ��������, ����>(��������, ���Ա����ָ��, ��, ����)
         *      *.BindCmd<��������, ��������, ����, ���Ա��������ֵ����>(��������, ���Ա����ָ��, ��, ����)
         */
        template<typename _Arg0, typename _BArg0, typename _T, typename _R>  // ����(_T:��)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (_T::*)(callback_param, _Arg0), binder::CmdOptionBindMFParamList1<_T, _BArg0> > > 
            BindCmd(const std::string strCmd, _R (_T::*fn)(callback_param, _Arg0), _T& t, _BArg0 arg0)
        {
            typedef _R (_T::*F)(callback_param, _Arg0); 
            typedef binder::CmdOptionBindMFParamList1<_T, _BArg0> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(t, arg0)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _BArg0, typename _BArg1, typename _T, typename _R>  // ����(_T:��)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (_T::*)(callback_param, _Arg0, _Arg1), binder::CmdOptionBindMFParamList2<_T, _BArg0, _BArg1> > > 
            BindCmd(const std::string strCmd, _R (_T::*fn)(callback_param, _Arg0, _Arg1), _T& t, _BArg0 arg0, _BArg1 arg1)
        {
            typedef _R (_T::*F)(callback_param, _Arg0, _Arg1); 
            typedef binder::CmdOptionBindMFParamList2<_T, _BArg0, _BArg1> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(t, arg0, arg1)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _Arg2, typename _BArg0, typename _BArg1, typename _BArg2, typename _T, typename _R>  // ����(_T:��)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (_T::*)(callback_param, _Arg0, _Arg1, _Arg2), binder::CmdOptionBindMFParamList3<_T, _BArg0, _BArg1, _BArg2> > > 
            BindCmd(const std::string strCmd, _R (_T::*fn)(callback_param, _Arg0, _Arg1, _Arg2), _T& t, _BArg0 arg0, _BArg1 arg1, _BArg2 arg2)
        {
            typedef _R (_T::*F)(callback_param, _Arg0, _Arg1, _Arg2); 
            typedef binder::CmdOptionBindMFParamList3<_T, _BArg0, _BArg1, _BArg2> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(t, arg0, arg1, arg2)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        /**
         * ����ͨ�������޲�����
         * example:
         *      *.BindCmd(��������, ����ָ��)
         *      *.BindCmd<��������ֵ����>(��������, ����ָ��)
         */
        template<typename _R>   // �󶨺���(_R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (*)(callback_param), binder::CmdOptionBindParamList0> > 
            BindCmd(const std::string strCmd, _R (*fn)(callback_param))
        {
            typedef _R (*F)(callback_param); 
            typedef binder::CmdOptionBindParamList0 list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type()));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        /**
         * ����ͨ����
         * BindCmd: �󶨲���[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ]
         * example:
         *      *.BindCmd(��������, ����ָ��, ����)                           // Ĭ�������ƶ��Ǵ�ֵ��������
         *      *.BindCmd<��������, ��������>(��������, ����ָ��, ����)
         *      *.BindCmd<��������, ��������, ��������ֵ����>(��������, ����ָ��, ����)
         */
        template<typename _Arg0, typename _BArg0, typename _R>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (*)(callback_param, _Arg0), binder::CmdOptionBindParamList1<_BArg0> > >
            BindCmd(const std::string strCmd, _R (*fn)(callback_param, _Arg0), _BArg0 arg0)
        {
            typedef _R (*F)(callback_param, _Arg0); 
            typedef binder::CmdOptionBindParamList1<_BArg0> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(arg0)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _BArg0, typename _BArg1, typename _R>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (*)(callback_param, _Arg0, _Arg1), binder::CmdOptionBindParamList2<_BArg0, _BArg1> > >
            BindCmd(const std::string strCmd, _R (*fn)(callback_param, _Arg0, _Arg1), _BArg0 arg0, _BArg1 arg1)
        {
            typedef _R (*F)(callback_param, _Arg0, _Arg1); 
            typedef binder::CmdOptionBindParamList2<_BArg0, _BArg1> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(arg0, arg1)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _Arg2, typename _BArg0, typename _BArg1, typename _BArg2, typename _R>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<_R, _R (*)(callback_param, _Arg0, _Arg1, _Arg2), binder::CmdOptionBindParamList3<_BArg0, _BArg1, _BArg2> > >
            BindCmd(const std::string strCmd, _R (*fn)(callback_param, _Arg0, _Arg1, _Arg2), _BArg0 arg0, _BArg1 arg1, _BArg2 arg2)
        {
            typedef _R (*F)(callback_param, _Arg0, _Arg1, _Arg2); 
            typedef binder::CmdOptionBindParamList3<_BArg0, _BArg1, _BArg2> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<_R, F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<_R, F, list_type>(fn, list_type(arg0, arg1, arg2)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        /**
         * �󶨺�������(����Ӧ)
         * ע�⣺Ĭ�ϻḴ�ƺ�������
         *
         * BindCmd: �󶨲���[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ]
         * example:
         *      *.BindCmd(��������, ��������, ����)                           // Ĭ�������ƶ��Ǵ�ֵ��������
         *      *.BindCmd<��������>(��������, ����ָ��, ����)
         */
        template<typename _F>   // �󶨺���(_F: ������������)
        std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, binder::CmdOptionBindParamList0> > 
            BindCmd(const std::string strCmd, _F fn)
        {
            typedef binder::CmdOptionBindParamList0 list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<binder::unspecified, _F, list_type>(fn, list_type()));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _F>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, binder::CmdOptionBindParamList1<_Arg0> > >
            BindCmd(const std::string strCmd, _F fn, _Arg0 arg0)
        {
            typedef binder::CmdOptionBindParamList1<_Arg0> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<binder::unspecified, _F, list_type>(fn, list_type(arg0)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _F>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, binder::CmdOptionBindParamList2<_Arg0, _Arg1> > >
            BindCmd(const std::string strCmd, _F fn, _Arg0 arg0, _Arg1 arg1)
        {
            typedef binder::CmdOptionBindParamList2<_Arg0, _Arg1> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<binder::unspecified, _F, list_type>(fn, list_type(arg0, arg1)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }

        template<typename _Arg0, typename _Arg1, typename _Arg2, typename _F>  // �󶨺���(_Arg:����[ע��ֵ�ĸ��Ʒ����ڱ�����ִ��ʱ], _R: �󶨺�������ֵ����)
        std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, binder::CmdOptionBindParamList3<_Arg0, _Arg1, _Arg2> > >
            BindCmd(const std::string strCmd, _F fn, _Arg0 arg0, _Arg1 arg1, _Arg2 arg2)
        {
            typedef binder::CmdOptionBindParamList3<_Arg0, _Arg1, _Arg2> list_type;
            typedef std::shared_ptr<binder::CmdOptionBindT<binder::unspecified, _F, list_type> > obj_type;

            obj_type pFun = obj_type(new binder::CmdOptionBindT<binder::unspecified, _F, list_type>(fn, list_type(arg0, arg1, arg2)));

            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pFun;
            }

            return pFun;
        }


        /**
         * ��ָ��(ͨ��)
         * BindCmd: �󶨲���
         * example:
         *      *.BindCmd(��������, binder::CmdOptionBindBase �ṹ����ָ��)
         *      *.BindCmd(��������, CmdOptionBind<TCmdStr> �ṹ����)
         * �Ƽ�ʹ����һ�֣����Լ���һ�νṹ����
         */
        std::shared_ptr<binder::CmdOptionBindBase> BindChildCmd(const std::string strCmd, std::shared_ptr<binder::CmdOptionBindBase> pBase)
        {
            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pBase;
            }

            return pBase;
        }
        std::shared_ptr<binder::CmdOptionBindBase> BindChildCmd(const std::string strCmd, const CmdOptionBind<TCmdStr>& stCmdOpt)
        {
            std::shared_ptr<binder::CmdOptionBindBase> pBase = std::shared_ptr<CmdOptionBind<TCmdStr> >(new CmdOptionBind<TCmdStr>(stCmdOpt));
            std::vector<std::string> stCmds = splitCmd(strCmd.c_str());
            for (std::vector<std::string>::size_type iIndex = 0; iIndex < stCmds.size(); ++ iIndex)
            {
                TCmdStr strTCmd = TCmdStr(stCmds[iIndex].c_str(), stCmds[iIndex].size());
                m_stCallbackFuns[strTCmd] = pBase;
            }

            return pBase;
        }
    };

    template<typename Ty>
    short CmdOptionBind<Ty>::m_strMapValue[256] = {0};

    // �����ض���
    typedef CmdOptionBind<std::string> CmdOption;
    typedef CmdOptionBind<CmdOptionCIString> CmdOptionCI;
}

#endif /* CMDOPTION_H_ */

/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_FUNCTION_2_H_
#define _QX_FUNCTION_2_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxFunction_2.h
 * \author Lionel Marty
 * \ingroup QxFunction
 * \brief Concrete function class registered into QxOrm context with 2 parameters
 */

#include <QxFunction/IxFunction.h>
#include <QxFunction/QxParameters.h>

namespace qx {

/*!
 * \ingroup QxFunction
 * \brief qx::QxFunction_2<Owner, R, P1, P2> : concrete function registered into QxOrm context defined into class Owner, returning an object of type R and with 2 parameters P1, P2
 */
template <class Owner, typename R, typename P1, typename P2>
class QxFunction_2 : public IxFunction
{

public:

   typedef boost::function<R (Owner *, P1, P2)> type_fct;
   typedef typename qx::trait::remove_attr<P1, false>::type type_P1;
   typedef typename qx::trait::remove_attr<P2, false>::type type_P2;
   QX_FUNCTION_CLASS_MEMBER_FCT(QxFunction_2);

   virtual int getParamCount() const                                    { return 2; }
   virtual qx_bool isValidParams(const QString & params) const          { Q_UNUSED(params); return true; }
   virtual qx_bool isValidParams(const type_any_params & params) const  { Q_UNUSED(params); return true; }

private:

   template <class T, bool bReturnValue /* = false */>
   struct QxInvokerFct
   {
      static inline qx_bool invoke(void * pOwner, const T & params, boost::any * ret, const QxFunction_2 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITH_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         try { pThis->m_fct(static_cast<Owner *>(pOwner), p1, p2); }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

   template <class T>
   struct QxInvokerFct<T, true>
   {
      static inline qx_bool invoke(void * pOwner, const T & params, boost::any * ret, const QxFunction_2 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITH_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         try { R retTmp = pThis->m_fct(static_cast<Owner *>(pOwner), p1, p2); if (ret) { (* ret) = boost::any(retTmp); } }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

};

template <typename R, typename P1, typename P2>
class QxFunction_2<void, R, P1, P2> : public IxFunction
{

public:

   typedef boost::function<R (P1, P2)> type_fct;
   typedef typename qx::trait::remove_attr<P1, false>::type type_P1;
   typedef typename qx::trait::remove_attr<P2, false>::type type_P2;
   QX_FUNCTION_CLASS_FCT(QxFunction_2);

   virtual int getParamCount() const                                    { return 2; }
   virtual qx_bool isValidParams(const QString & params) const          { Q_UNUSED(params); return true; }
   virtual qx_bool isValidParams(const type_any_params & params) const  { Q_UNUSED(params); return true; }

private:

   template <class T, bool bReturnValue /* = false */>
   struct QxInvokerFct
   {
      static inline qx_bool invoke(const T & params, boost::any * ret, const QxFunction_2 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITHOUT_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         try { pThis->m_fct(p1, p2); }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

   template <class T>
   struct QxInvokerFct<T, true>
   {
      static inline qx_bool invoke(const T & params, boost::any * ret, const QxFunction_2 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITHOUT_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         try { R retTmp = pThis->m_fct(p1, p2); if (ret) { (* ret) = boost::any(retTmp); } }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

};

namespace function {

template <class Owner, typename R, typename P1, typename P2>
IxFunction_ptr bind_fct_2(const typename QxFunction_2<Owner, R, P1, P2>::type_fct & fct)
{
   typedef boost::is_same<Owner, void> qx_verify_owner_tmp;
   BOOST_STATIC_ASSERT(qx_verify_owner_tmp::value);
   IxFunction_ptr ptr; ptr.reset(new QxFunction_2<void, R, P1, P2>(fct));
   return ptr;
}

template <class Owner, typename R, typename P1, typename P2>
IxFunction_ptr bind_member_fct_2(const typename QxFunction_2<Owner, R, P1, P2>::type_fct & fct)
{
   typedef boost::is_same<Owner, void> qx_verify_owner_tmp;
   BOOST_STATIC_ASSERT(! qx_verify_owner_tmp::value);
   IxFunction_ptr ptr; ptr.reset(new QxFunction_2<Owner, R, P1, P2>(fct));
   return ptr;
}

} // namespace function
} // namespace qx

#endif // _QX_FUNCTION_2_H_

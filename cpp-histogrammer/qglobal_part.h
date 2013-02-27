/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGLOBAL_PART_H
#define QGLOBAL_PARTH

#include <stddef.h>
#include <assert.h>

/*
   Utility macros and inline functions
*/
typedef short          qint16;
typedef unsigned short quint16;
typedef int            qint32;
typedef unsigned       quint32;
typedef long           qint64;
typedef unsigned long  quint64;
typedef float qreal;

#ifndef D_QABS
#define D_QABS
template <typename T>
inline T qAbs(const T &t) { return t >= 0 ? t : -t; }
#endif

#ifndef D_QMIN
#define D_QMIN
template <typename T>
inline T qMin(const T &a, const T &b) { return a <= b ? a : b; }
#endif

#ifndef D_QMAX
#define D_QMAX
template <typename T>
inline T qMax(const T &a, const T &b) { return a >= b ? a : b; }
#endif

#ifndef D_QROUND
#define D_QROUND
inline int qRound(qreal d)
{ return d >= qreal(0.0) ? int(d + qreal(0.5)) : int(d - int(d-1) + qreal(0.5)) + int(d-1); }
#endif

#ifndef D_QFUZZYCOMPARE_DOUBLE
#define D_QFUZZYCOMPARE_DOUBLE
static inline bool qFuzzyCompare(double p1, double p2)
{
    return (qAbs(p1 - p2) <= 0.000000000001 * qMin(qAbs(p1), qAbs(p2)));
}
#endif

#ifndef D_QFUZZYCOMPARE_FLOAT
#define D_QFUZZYCOMPARE_FLOAT
static inline bool qFuzzyCompare(float p1, float p2)
{
    return (qAbs(p1 - p2) <= 0.00001f * qMin(qAbs(p1), qAbs(p2)));
}
#endif

#ifndef D_QFUZZYISNULL_DOUBLE
#define D_QFUZZYISNULL_DOUBLE
/*!
  \internal
*/
static inline bool qFuzzyIsNull(double d)
{
    return qAbs(d) <= 0.000000000001;
}
#endif

#ifndef D_QFUZZYISNULL_FLOAT
#define D_QFUZZYISNULL_FLOAT
/*!
  \internal
*/
static inline bool qFuzzyIsNull(float f)
{
    return qAbs(f) <= 0.00001f;
}
#endif

#ifndef D_QISNULL_DOUBLE
#define D_QISNULL_DOUBLE
/*
   This function tests a double for a null value. It doesn't
   check whether the actual value is 0 or close to 0, but whether
   it is binary 0.
*/
static inline bool qIsNull(double d)
{
    union U {
        double d;
        quint64 u;
    };
    U val;
    val.d = d;
    return val.u == quint64(0);
}
#endif

#ifndef D_QISNULL_FLOAT
#define D_QISNULL_FLOAT
/*
   This function tests a float for a null value. It doesn't
   check whether the actual value is 0 or close to 0, but whether
   it is binary 0.
*/
static inline bool qIsNull(float f)
{
    union U {
        float f;
        quint32 u;
    };
    U val;
    val.f = f;
    return val.u == 0u;
}
#endif

#endif

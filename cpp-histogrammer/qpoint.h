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

#ifndef QPOINT_H
#define QPOINT_H

#include "qglobal_part.h"
#include <iostream>

class qpoint
{
public:
    qpoint();
    qpoint(int xpos, int ypos);

    bool isNull() const;

    int x() const;
    int y() const;
    void setX(int x);
    void setY(int y);

    int manhattanLength() const;

    int &rx();
    int &ry();

    qpoint &operator+=(const qpoint &p);
    qpoint &operator-=(const qpoint &p);

    qpoint &operator*=(float c);
    qpoint &operator*=(double c);
    qpoint &operator*=(int c);

    qpoint &operator/=(qreal c);

    friend inline bool operator==(const qpoint &, const qpoint &);
    friend inline bool operator!=(const qpoint &, const qpoint &);
    friend inline const qpoint operator+(const qpoint &, const qpoint &);
    friend inline const qpoint operator-(const qpoint &, const qpoint &);
    friend inline const qpoint operator*(const qpoint &, float);
    friend inline const qpoint operator*(float, const qpoint &);
    friend inline const qpoint operator*(const qpoint &, double);
    friend inline const qpoint operator*(double, const qpoint &);
    friend inline const qpoint operator*(const qpoint &, int);
    friend inline const qpoint operator*(int, const qpoint &);
    friend inline const qpoint operator-(const qpoint &);
    friend inline const qpoint operator/(const qpoint &, qreal);

private:
    int xp;
    int yp;

};


/*****************************************************************************
  qpoint stream functions
 *****************************************************************************/

std::ostream &operator<<(std::ostream &, const qpoint &);
std::istream &operator>>(std::istream &, qpoint &);


/*****************************************************************************
  qpoint inline functions
 *****************************************************************************/

inline qpoint::qpoint()
{ xp=0; yp=0; }

inline qpoint::qpoint(int xpos, int ypos)
{ xp = xpos; yp = ypos; }

inline bool qpoint::isNull() const
{ return xp == 0 && yp == 0; }

inline int qpoint::x() const
{ return xp; }

inline int qpoint::y() const
{ return yp; }

inline void qpoint::setX(int xpos)
{ xp = xpos; }

inline void qpoint::setY(int ypos)
{ yp = ypos; }

inline int &qpoint::rx()
{ return xp; }

inline int &qpoint::ry()
{ return yp; }

inline qpoint &qpoint::operator+=(const qpoint &p)
{ xp+=p.xp; yp+=p.yp; return *this; }

inline qpoint &qpoint::operator-=(const qpoint &p)
{ xp-=p.xp; yp-=p.yp; return *this; }

inline qpoint &qpoint::operator*=(float c)
{ xp = qRound(xp*c); yp = qRound(yp*c); return *this; }

inline qpoint &qpoint::operator*=(double c)
{ xp = qRound(xp*c); yp = qRound(yp*c); return *this; }

inline qpoint &qpoint::operator*=(int c)
{ xp = xp*c; yp = yp*c; return *this; }

inline bool operator==(const qpoint &p1, const qpoint &p2)
{ return p1.xp == p2.xp && p1.yp == p2.yp; }

inline bool operator!=(const qpoint &p1, const qpoint &p2)
{ return p1.xp != p2.xp || p1.yp != p2.yp; }

inline const qpoint operator+(const qpoint &p1, const qpoint &p2)
{ return qpoint(p1.xp+p2.xp, p1.yp+p2.yp); }

inline const qpoint operator-(const qpoint &p1, const qpoint &p2)
{ return qpoint(p1.xp-p2.xp, p1.yp-p2.yp); }

inline const qpoint operator*(const qpoint &p, float c)
{ return qpoint(qRound(p.xp*c), qRound(p.yp*c)); }

inline const qpoint operator*(const qpoint &p, double c)
{ return qpoint(qRound(p.xp*c), qRound(p.yp*c)); }

inline const qpoint operator*(const qpoint &p, int c)
{ return qpoint(p.xp*c, p.yp*c); }

inline const qpoint operator*(float c, const qpoint &p)
{ return qpoint(qRound(p.xp*c), qRound(p.yp*c)); }

inline const qpoint operator*(double c, const qpoint &p)
{ return qpoint(qRound(p.xp*c), qRound(p.yp*c)); }

inline const qpoint operator*(int c, const qpoint &p)
{ return qpoint(p.xp*c, p.yp*c); }

inline const qpoint operator-(const qpoint &p)
{ return qpoint(-p.xp, -p.yp); }

inline qpoint &qpoint::operator/=(qreal c)
{
    xp = qRound(xp/c);
    yp = qRound(yp/c);
    return *this;
}

inline const qpoint operator/(const qpoint &p, qreal c)
{
    return qpoint(qRound(p.xp/c), qRound(p.yp/c));
}


class qpointf
{
public:
    qpointf();
    qpointf(const qpoint &p);
    qpointf(qreal xpos, qreal ypos);

    qreal manhattanLength() const;

    bool isNull() const;

    qreal x() const;
    qreal y() const;
    void setX(qreal x);
    void setY(qreal y);

    qreal &rx();
    qreal &ry();

    qpointf &operator+=(const qpointf &p);
    qpointf &operator-=(const qpointf &p);
    qpointf &operator*=(qreal c);
    qpointf &operator/=(qreal c);

    friend inline bool operator==(const qpointf &, const qpointf &);
    friend inline bool operator!=(const qpointf &, const qpointf &);
    friend inline const qpointf operator+(const qpointf &, const qpointf &);
    friend inline const qpointf operator-(const qpointf &, const qpointf &);
    friend inline const qpointf operator*(qreal, const qpointf &);
    friend inline const qpointf operator*(const qpointf &, qreal);
    friend inline const qpointf operator-(const qpointf &);
    friend inline const qpointf operator/(const qpointf &, qreal);

    qpoint toPoint() const;

private:
    friend class QMatrix;
    friend class QTransform;

    qreal xp;
    qreal yp;
};

/*****************************************************************************
  qpointf stream functions
 *****************************************************************************/

std::ostream &operator<<(std::ostream &, const qpointf &);
std::ostream &operator>>(std::ostream &, qpointf &);


/*****************************************************************************
  qpointf inline functions
 *****************************************************************************/

inline qpointf::qpointf() : xp(0), yp(0) { }

inline qpointf::qpointf(qreal xpos, qreal ypos) : xp(xpos), yp(ypos) { }

inline qpointf::qpointf(const qpoint &p) : xp(p.x()), yp(p.y()) { }

inline bool qpointf::isNull() const
{
    return qIsNull(xp) && qIsNull(yp);
}

inline qreal qpointf::x() const
{
    return xp;
}

inline qreal qpointf::y() const
{
    return yp;
}

inline void qpointf::setX(qreal xpos)
{
    xp = xpos;
}

inline void qpointf::setY(qreal ypos)
{
    yp = ypos;
}

inline qreal &qpointf::rx()
{
    return xp;
}

inline qreal &qpointf::ry()
{
    return yp;
}

inline qpointf &qpointf::operator+=(const qpointf &p)
{
    xp+=p.xp;
    yp+=p.yp;
    return *this;
}

inline qpointf &qpointf::operator-=(const qpointf &p)
{
    xp-=p.xp; yp-=p.yp; return *this;
}

inline qpointf &qpointf::operator*=(qreal c)
{
    xp*=c; yp*=c; return *this;
}

inline bool operator==(const qpointf &p1, const qpointf &p2)
{
    return qFuzzyIsNull(p1.xp - p2.xp) && qFuzzyIsNull(p1.yp - p2.yp);
}

inline bool operator!=(const qpointf &p1, const qpointf &p2)
{
    return !qFuzzyIsNull(p1.xp - p2.xp) || !qFuzzyIsNull(p1.yp - p2.yp);
}

inline const qpointf operator+(const qpointf &p1, const qpointf &p2)
{
    return qpointf(p1.xp+p2.xp, p1.yp+p2.yp);
}

inline const qpointf operator-(const qpointf &p1, const qpointf &p2)
{
    return qpointf(p1.xp-p2.xp, p1.yp-p2.yp);
}

inline const qpointf operator*(const qpointf &p, qreal c)
{
    return qpointf(p.xp*c, p.yp*c);
}

inline const qpointf operator*(qreal c, const qpointf &p)
{
    return qpointf(p.xp*c, p.yp*c);
}

inline const qpointf operator-(const qpointf &p)
{
    return qpointf(-p.xp, -p.yp);
}

inline qpointf &qpointf::operator/=(qreal c)
{
    xp/=c;
    yp/=c;
    return *this;
}

inline const qpointf operator/(const qpointf &p, qreal c)
{
    return qpointf(p.xp/c, p.yp/c);
}

inline qpoint qpointf::toPoint() const
{
    return qpoint(qRound(xp), qRound(yp));
}


#endif // QPOINT_H


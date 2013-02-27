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

#include "qpoint.h"


/*!
    \class qpoint
    \ingroup painting

    \brief The qpoint class defines a point in the plane using integer
    precision.

    A point is specified by a x coordinate and an y coordinate which
    can be accessed using the x() and y() functions. The isNull()
    function returns true if both x and y are set to 0. The
    coordinates can be set (or altered) using the setX() and setY()
    functions, or alternatively the rx() and ry() functions which
    return references to the coordinates (allowing direct
    manipulation).

    Given a point \e p, the following statements are all equivalent:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 0

    A qpoint object can also be used as a vector: Addition and
    subtraction are defined as for vectors (each component is added
    separately). A qpoint object can also be divided or multiplied by
    an \c int or a \c qreal.

    In addition, the qpoint class provides the manhattanLength()
    function which gives an inexpensive approximation of the length of
    the qpoint object interpreted as a vector. Finally, qpoint objects
    can be streamed as well as compared.

    \sa qpointf, QPolygon
*/


/*****************************************************************************
  qpoint member functions
 *****************************************************************************/

/*!
    \fn qpoint::qpoint()

    Constructs a null point, i.e. with coordinates (0, 0)

    \sa isNull()
*/

/*!
    \fn qpoint::qpoint(int x, int y)

    Constructs a point with the given coordinates (\a x, \a  y).

    \sa setX(), setY()
*/

/*!
    \fn bool qpoint::isNull() const

    Returns true if both the x and y coordinates are set to 0,
    otherwise returns false.
*/

/*!
    \fn int qpoint::x() const

    Returns the x coordinate of this point.

    \sa setX(), rx()
*/

/*!
    \fn int qpoint::y() const

    Returns the y coordinate of this point.

    \sa setY(), ry()
*/

/*!
    \fn void qpoint::setX(int x)

    Sets the x coordinate of this point to the given \a x coordinate.

    \sa x() setY()
*/

/*!
    \fn void qpoint::setY(int y)

    Sets the y coordinate of this point to the given \a y coordinate.

    \sa y() setX()
*/


/*!
    \fn int &qpoint::rx()

    Returns a reference to the x coordinate of this point.

    Using a reference makes it possible to directly manipulate x. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 1

    \sa x() setX()
*/

/*!
    \fn int &qpoint::ry()

    Returns a reference to the y coordinate of this point.

    Using a reference makes it possible to directly manipulate y. For
    example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 2

    \sa y(), setY()
*/


/*!
    \fn qpoint &qpoint::operator+=(const qpoint &point)

    Adds the given \a point to this point and returns a reference to
    this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 3

    \sa operator-=()
*/

/*!
    \fn qpoint &qpoint::operator-=(const qpoint &point)

    Subtracts the given \a point from this point and returns a
    reference to this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 4

    \sa operator+=()
*/

/*!
    \fn qpoint &qpoint::operator*=(float factor)
    \since 4.8

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use qpointf for floating point accuracy.

    \sa operator/=()
*/

/*!
    \fn qpoint &qpoint::operator*=(double factor)
    \since 4.8

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 5

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use qpointf for floating point accuracy.

    \sa operator/=()
*/

/*!
    \fn qpoint &qpoint::operator*=(int factor)
    \since 4.8

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point.

    \sa operator/=()
*/

/*!
    \fn bool operator==(const qpoint &p1, const qpoint &p2)
    \relates qpoint

    Returns true if \a p1 and \a p2 are equal; otherwise returns
    false.
*/

/*!
    \fn bool operator!=(const qpoint &p1, const qpoint &p2)
    \relates qpoint

    Returns true if \a p1 and \a p2 are not equal; otherwise returns false.
*/

/*!
    \fn const qpoint operator+(const qpoint &p1, const qpoint &p2)
    \relates qpoint

    Returns a qpoint object that is the sum of the given points, \a p1
    and \a p2; each component is added separately.

    \sa qpoint::operator+=()
*/

/*!
    \fn const qpoint operator-(const qpoint &p1, const qpoint &p2)
    \relates qpoint

    Returns a qpoint object that is formed by subtracting \a p2 from
    \a p1; each component is subtracted separately.

    \sa qpoint::operator-=()
*/

/*!
    \fn const qpoint operator*(const qpoint &point, float factor)
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use qpointf for floating point accuracy.

    \sa qpoint::operator*=()
*/

/*!
    \fn const qpoint operator*(const qpoint &point, double factor)
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use qpointf for floating point accuracy.

    \sa qpoint::operator*=()
*/

/*!
    \fn const qpoint operator*(const qpoint &point, int factor)
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.

    \sa qpoint::operator*=()
*/

/*!
    \fn const qpoint operator*(float factor, const qpoint &point)
    \overload
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.
*/

/*!
    \fn const qpoint operator*(double factor, const qpoint &point)
    \overload
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.
*/

/*!
    \fn const qpoint operator*(int factor, const qpoint &point)
    \overload
    \relates qpoint
    \since 4.8

    Returns a copy of the given \a point multiplied by the given \a factor.
*/

/*!
    \fn const qpoint operator-(const qpoint &point)
    \overload
    \relates qpoint

    Returns a qpoint object that is formed by changing the sign of
    both components of the given \a point.

    Equivalent to \c{qpoint(0,0) - point}.
*/

/*!
    \fn qpoint &qpoint::operator/=(qreal divisor)
    \overload

    Divides both x and y by the given \a divisor, and returns a reference to this
    point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 6

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use qpointf for floating point accuracy.

    \sa operator*=()
*/

/*!
    \fn const qpoint operator/(const qpoint &point, qreal divisor)
    \relates qpoint

    Returns the qpoint formed by dividing both components of the given \a point
    by the given \a divisor.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use qpointf for floating point accuracy.

    \sa qpoint::operator/=()
*/

/*!
    Returns the sum of the absolute values of x() and y(),
    traditionally known as the "Manhattan length" of the vector from
    the origin to the point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 7

    This is a useful, and quick to calculate, approximation to the
    true length:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 8

    The tradition of "Manhattan length" arises because such distances
    apply to travelers who can only travel on a rectangular grid, like
    the streets of Manhattan.
*/
int qpoint::manhattanLength() const
{
    return qAbs(x())+qAbs(y());
}


/*!
    \class qpointf
    \ingroup painting

    \brief The qpointf class defines a point in the plane using
    floating point precision.

    A point is specified by a x coordinate and an y coordinate which
    can be accessed using the x() and y() functions. The coordinates
    of the point are specified using floating point numbers for
    accuracy. The isNull() function returns true if both x and y are
    set to 0.0. The coordinates can be set (or altered) using the setX()
    and setY() functions, or alternatively the rx() and ry() functions which
    return references to the coordinates (allowing direct
    manipulation).

    Given a point \e p, the following statements are all equivalent:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 9

    A qpointf object can also be used as a vector: Addition and
    subtraction are defined as for vectors (each component is added
    separately). A qpointf object can also be divided or multiplied by
    an \c int or a \c qreal.

    In addition, the qpointf class provides a constructor converting a
    qpoint object into a qpointf object, and a corresponding toPoint()
    function which returns a qpoint copy of \e this point. Finally,
    qpointf objects can be streamed as well as compared.

    \sa qpoint, QPolygonF
*/

/*!
    \fn qpointf::qpointf()

    Constructs a null point, i.e. with coordinates (0.0, 0.0)

    \sa isNull()
*/

/*!
    \fn qpointf::qpointf(const qpoint &point)

    Constructs a copy of the given \a point.

    \sa toPoint()
*/

/*!
    \fn qpointf::qpointf(qreal x, qreal y)

    Constructs a point with the given coordinates (\a x, \a y).

    \sa setX(), setY()
*/

/*!
    \fn bool qpointf::isNull() const

    Returns true if both the x and y coordinates are set to +0.0;
    otherwise returns false.

    \note Since this function treats +0.0 and -0.0 differently, points
    with zero-valued coordinates where either or both values have a
    negative sign are not defined to be null points.
*/


/*!
    \since 4.6

    Returns the sum of the absolute values of x() and y(),
    traditionally known as the "Manhattan length" of the vector from
    the origin to the point.

    \sa qpoint::manhattanLength()
*/
qreal qpointf::manhattanLength() const
{
    return qAbs(x())+qAbs(y());
}

/*!
    \fn qreal qpointf::x() const

    Returns the x-coordinate of this point.

    \sa setX(), rx()
*/

/*!
    \fn qreal qpointf::y() const

    Returns the y-coordinate of this point.

    \sa setY(), ry()
*/

/*!
    \fn void qpointf::setX(qreal x)

    Sets the x coordinate of this point to the given \a x coordinate.

    \sa x() setY()
*/

/*!
    \fn void qpointf::setY(qreal y)

    Sets the y coordinate of this point to the given \a y coordinate.

    \sa  y(), setX()
*/

/*!
    \fn qreal& qpointf::rx()

    Returns a reference to the x coordinate of this point.

    Using a reference makes it possible to directly manipulate x. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 10

    \sa x(), setX()
*/

/*!
    \fn qreal& qpointf::ry()

    Returns a reference to the y coordinate of this point.

    Using a reference makes it possible to directly manipulate y. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 11

    \sa y() setY()
*/

/*!
    \fn qpointf& qpointf::operator+=(const qpointf &point)

    Adds the given \a point to this point and returns a reference to
    this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 12

    \sa operator-=()
*/

/*!
    \fn qpointf& qpointf::operator-=(const qpointf &point)

    Subtracts the given \a point from this point and returns a reference
    to this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 13

    \sa operator+=()
*/

/*!
    \fn qpointf& qpointf::operator*=(qreal factor)

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 14

    \sa operator/=()
*/

/*!
    \fn qpointf& qpointf::operator/=(qreal divisor)

    Divides both x and y by the given \a divisor, and returns a reference
    to this point. For example:

    \snippet doc/src/snippets/code/src_corelib_tools_qpoint.cpp 15

    \sa operator*=()
*/

/*!
    \fn const qpointf operator+(const qpointf &p1, const qpointf &p2)
    \relates qpointf

    Returns a qpointf object that is the sum of the given points, \a p1
    and \a p2; each component is added separately.

    \sa qpointf::operator+=()
*/

/*!
    \fn const qpointf operator-(const qpointf &p1, const qpointf &p2)
    \relates qpointf

    Returns a qpointf object that is formed by subtracting \a p2 from \a p1;
    each component is subtracted separately.

    \sa qpointf::operator-=()
*/

/*!
    \fn const qpointf operator*(const qpointf &point, qreal factor)
    \relates qpointf

    Returns a copy of the given \a point,  multiplied by the given \a factor.

    \sa qpointf::operator*=()
*/

/*!
    \fn const qpointf operator*(qreal factor, const qpointf &point)
    \relates qpointf

    \overload

    Returns a copy of the given \a point, multiplied by the given \a factor.
*/

/*!
    \fn const qpointf operator-(const qpointf &point)
    \relates qpointf
    \overload

    Returns a qpointf object that is formed by changing the sign of
    both components of the given \a point.

    Equivalent to \c {qpointf(0,0) - point}.
*/

/*!
    \fn const qpointf operator/(const qpointf &point, qreal divisor)
    \relates qpointf

    Returns the qpointf object formed by dividing both components of
    the given \a point by the given \a divisor.

    \sa qpointf::operator/=()
*/

/*!
    \fn qpoint qpointf::toPoint() const

    Rounds the coordinates of this point to the nearest integer, and
    returns a qpoint object with the rounded coordinates.

    \sa qpointf()
*/

/*!
    \fn bool operator==(const qpointf &p1, const qpointf &p2)
    \relates qpointf

    Returns true if \a p1 is equal to \a p2; otherwise returns false.
*/

/*!
    \fn bool operator!=(const qpointf &p1, const qpointf &p2);
    \relates qpointf

    Returns true if \a p1 is not equal to \a p2; otherwise returns false.
*/


/*!
    \fn std::ostream &operator<<(std::ostream &stream, const qpointf &point)
    \relates qpointf

    Writes the given \a point to the given \a stream and returns a
    reference to the stream.

    \sa {Serializing Qt Data Types}
*/

std::ostream &operator<<(std::ostream &s, const qpointf &p)
{
    s << double(p.x()) << double(p.y());
    return s;
}

/*!
    \fn std::ostream &operator>>(std::ostream &stream, qpointf &point)
    \relates qpointf

    Reads a point from the given \a stream into the given \a point
    and returns a reference to the stream.

    \sa {Serializing Qt Data Types}
*/

std::istream &operator>>(std::istream &s, qpointf &p)
{
    double x, y;
    s >> x;
    s >> y;
    p.setX(qreal(x));
    p.setY(qreal(y));
    return s;
}




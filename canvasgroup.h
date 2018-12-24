/*
    Copyright (C) 1992-2003 Trolltech AS. All Rights Reserved.

    This file ("Example Code"), is part of an example program for Qt,
    and is licensed under the Qt Commercial License Agreement,
    Agreement version 2.4 and higher as well as under the GPL.

    The Example Code is licensed to you "as is" without warranty of
    any kind. To the maximum extent permitted by applicable law,
    Trolltech on behalf of itself and its suppliers, disclaims all
    warranties express or implied, including, but not limited to,
    implied warranties of merchantability and fitness for a particular
    purpose with regard to the Example Code. Trolltech does not
    warrant that the Example Code will satisfy your requirements or
    that it is without defect or error or that the operation thereof
    will be uninterrupted. All use of and reliance on the Example Code
    is at the sole risk of and responsibility of you and your
    customers.

    If you are a holder of a Qt Commercial License Agreement, you can
    use the code under that agreement or you can use it under GPL. If
    you are not a holder of a Qt Commercial License Agreement, you can
    use the code under the GPL. Regardless of the applicable license
    agreement, the Example Code may be used, distributed and modified
    without limitation.
*/


#ifndef CANVASGROUP_H
#define CANVASGROUP_H

#include <qmap.h>
#include <qptrlist.h>

class QCanvasItem;
class QRect;

class CanvasGroup
{
public:
    typedef QPtrList<QCanvasItem> CList;
    typedef QPtrListIterator<QCanvasItem> CListIter;

    CanvasGroup() {} // Constructs an empty group
    ~CanvasGroup();

    void add( QCanvasItem* );
    bool remove( QCanvasItem* );
    void moveBy( double, double );
    QRect boundingRect() const;
    bool contains(const QCanvasItem* ) const;
    int count() const { return items.count(); }

    static CanvasGroup* groupContaining( QCanvasItem* );
    static CanvasGroup* merge( QCanvasItem*, QCanvasItem* );
    static CanvasGroup* merge( CList );

private:
    CList items;
    typedef QMap<QCanvasItem*,CanvasGroup*> GroupMap;
    static GroupMap& groupMap();
};

#endif // CANVASGROUP_H

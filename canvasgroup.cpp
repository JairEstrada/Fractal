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

#include "canvasgroup.h"

#include <qcanvas.h>

/*
  Destroys the group. Any items that were members continue
  to exist, but are no longer in a group.
*/
CanvasGroup::~CanvasGroup()
{
    for ( CListIter it(items); *it; ++it )
	groupMap().remove( *it );
}


/*
  Adds item to the group, removing it from any previous group.
*/
void CanvasGroup::add( QCanvasItem* item )
{
    CanvasGroup*& mapping = groupMap()[item];
    if ( mapping ) {
         if ( mapping == this )
             return;
         mapping->items.removeRef( item );
         if ( mapping->items.isEmpty() )
             delete mapping;
    }

    items.prepend( item );
    mapping = this;
}


/*
  Removes item from the group, returning TRUE if it was a member.
*/
bool CanvasGroup::remove( QCanvasItem* item )
{
    groupMap().remove( item );
    if ( items.removeRef(item ) ) {
	if ( items.isEmpty() )
	    delete this;
	return TRUE;
    } else
	return FALSE;
}

/*
  Moves all items in the group by the vector (dx,dy).
*/
void CanvasGroup::moveBy( double dx, double dy )
{
    for ( CListIter it(items); *it; ++it )
	(*it)->moveBy( dx, dy );
}

/*
  Returns the QRect that includes the boundingRect() of all items in the group.
*/
QRect CanvasGroup::boundingRect() const
{
    QRect rect;
    for ( CListIter it(items); *it; ++it )
	rect |= (*it)->boundingRect();
    return rect;
}

/*
  Returns TRUE if item is in the group.
*/
bool CanvasGroup::contains( const QCanvasItem* item ) const
{
    for ( CListIter it(items); *it; ++it )
	if ( *it == item )
	    return TRUE;
    return FALSE;
}

/*
  Returns the group containing item.
*/
CanvasGroup* CanvasGroup::groupContaining( QCanvasItem* item )
{
    GroupMap::ConstIterator it = groupMap().find( item );
    if ( it == groupMap().end() )
	return 0;
    else
	return *it;
}

/*
  Groups item1 and item2. Any items previously grouped with the items
  are also combined into the resulting group.
*/
CanvasGroup* CanvasGroup::merge(QCanvasItem* item1, QCanvasItem* item2)
{
    CanvasGroup* group1 = groupContaining(item1);
    CanvasGroup* group2 = groupContaining(item2);
    if ( group1 ) {
	if ( group2 ) {
	    if ( group1 == group2 )
		return group1;
	    // Combine groups
	    for ( CListIter it(group2->items); *it; ++it )
		group1->add( *it );
	    delete group2;
	} else
	    group1->add( item2 );
	return group1;
    } else if ( group2 ) {
	group2->add( item1 );
	return group2;
    } else { // New group
	group1 = new CanvasGroup;
	group1->add( item1 );
	group1->add( item2 );
	return group1;
    }
}

/*
  Groups a list of items. Any items previously grouped with the items
  are also combined into the resulting group.
*/
CanvasGroup* CanvasGroup::merge( CList list )
{
    if ( !list.isEmpty() ) {
	CListIter it(list);
	QCanvasItem* first = *it;
	++it;
	while ( *it ) {
	    merge( first, *it );
	    ++it;
	}
    }
}

/*
  Internal.
*/
QMap<QCanvasItem*,CanvasGroup*>& CanvasGroup::groupMap()
{
    static GroupMap *group = 0;
    if ( !group )
	group = new GroupMap;
    return *group;
}


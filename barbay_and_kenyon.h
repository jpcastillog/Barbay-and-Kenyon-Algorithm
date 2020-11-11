#ifndef BARBAY_AND_KENYON_H_
#define BARBAY_AND_KENYON_H_

#include <iostream>
#include <list>
#include <queue>
#include "dip.h"

template <typename T>
int barbayKenyon(Set<T> *sets, int k, list<T> *intersection);

template <typename T>
int forceBruteIntersection(Set<T> *sets, int k, list<T> *intersection);

template <typename T>
int intervalBarbayKenyon(IntervalSet<T> *sets, int k, list< Interval<T> > *intersection);

template <typename T>
void intersectionDIP(heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions1, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions2, list< Interval<T> > *intersection);

#endif
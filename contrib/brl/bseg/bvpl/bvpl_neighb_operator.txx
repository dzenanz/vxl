#ifndef bvpl_neighb_operator_txx_
#define bvpl_neighb_operator_txx_

#include "bvpl_neighb_operator.h"


template <class T, class F>
void bvpl_neighb_operator<T,F>::operator()(bvpl_subgrid_iterator<T>& subgrid_iter, 
                                         bvpl_kernel_iterator& kernel_iter, 
                                         bvpl_subgrid_iterator<T>& output_iter)
{
  while (!subgrid_iter.isDone()) {
    bvpl_voxel_subgrid<T> grid = *subgrid_iter;
    while (!kernel_iter.isDone()) {
      vgl_point_3d<int> idx = kernel_iter.index();
      T val;
      if (grid.voxel(idx, val)) {
        bvpl_kernel_dispatch d = *kernel_iter;
        func_.apply(val, d);
      }
      ++kernel_iter;
    }
    (*output_iter).set_voxel(func_.result());
    ++subgrid_iter;
   }
}

#define BVPL_NEIGHB_OPER_INSTANTIATE(T,F) \
template class bvpl_neighb_operator<T,F>
                                      
#endif
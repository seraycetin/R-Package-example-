module fortloop
  use, intrinsic :: iso_c_binding

  implicit none
  private
  public :: llc_f, add_f

  contains

    subroutine llc_f(x, n, l, a, llc) bind(C, name = "llc_f_")

      real(kind = c_double), intent(in)               :: l, a !limit & attach
      integer(kind = c_int), intent(in), value        :: n    !Length of x
      real(kind = c_double), intent(in), dimension(n) :: x    !Vector of loss
      real(kind = c_double), intent(out)              :: llc  !Output variable
      integer                                         :: i    !Internal count

      llc = 0.0_c_double
      do i = 1, n
        llc = llc + max(0.0_c_double, min(x(i) - a, l))
      end do

    end subroutine llc_f


    subroutine add_f(a, b, ret) bind(C, name = "add_f_")

      real(kind = c_double), intent(in)               :: a, b !limit & attach
      real(kind = c_double), intent(out)              :: ret  !Output variable
      integer                                         :: i    !Internal count

      ret = 0.0_c_double
      do i = 1, b
        ret = ret + a
      end do

    end subroutine add_f

end module fortloop

#ifndef LIBPORT_UFLOAT_H
# define LIBPORT_UFLOAT_H

// Floating point definition (emulated or real)
# include "libport/ufloat.hh"

// Currently we don't prefix all the uses in the kernel.
using libport::ufloat;
using libport::PI;
using libport::UINFINITY;

# ifndef HAVE_ROUND
using libport::round;
# endif /* !HAVE_ROUND */

#endif // !LIBPORT_UFLOAT_H

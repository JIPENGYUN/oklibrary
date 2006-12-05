// Oliver Kullmann, 5.12.2006 (Swansea)

/*!
  \file Literals/traits/var_type.hpp
  \brief Traits-metafunctions to extract the variables type
*/

#ifndef VARTYPE_jdnNBv63
#define VARTYPE_jdnNBv63

namespace OKlib {
  namespace Literals {
    namespace traits {

      /*!
        \class var_type
        \brief Traits meta-function to extract the variables type.
      */
      
      template <typename L>
      struct var_type {
        typedef typename L::var_type type;
      };
      
    }

    /*!
      \brief Simple catch-all function template to extract variables from literals
      \todo Where to put this?
      \todo Is this default implementation sensible?
    */

    template <typename L>
    typename traits::var_type<L>::type var(const L& x) {
      return static_cast<typename traits::var_type<L>::type>(x);
    }

  }

}

#endif

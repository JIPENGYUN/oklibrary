// Oliver Kullmann, 28.8.2005 (Swansea)

/*!
  \namespace OKlib::Refactoring
  \brief Tools for refactoring C++ code.
*/

/*!
  \file IncludeHandling.hpp
  \brief Refactoring of include directives.
*/

#ifndef INCLUDEHANDLING_9yhNbv

#define INCLUDEHANDLING_9yhNbv

#include <string>
#include <cassert>

namespace OKlib {

  namespace Refactoring {

    enum Include_forms { system_header, source_code_header };

    /*!
      \class IncludeDirective
      \brief Representation of one include directive.
      \todo Enable element access.
      \todo Enable output streaming.
    */
    
    template <class String = std::string>
    class IncludeDirective {
    public :
      typedef typename String::size_type size_type;
    private :
      String header_file;
      size_type number_spaces_after_hash, number_spaces_after_include;
      Include_forms include_form;
    public :
      IncludeDirective(const String& header_file, const size_type number_spaces_after_hash,  const size_type number_spaces_2, const Include_forms include_form) : header_file(header_file), number_spaces_after_hash(number_spaces_after_hash), number_spaces_after_include(number_spaces_after_include), include_form(include_form) {
        assert(not header_file.empty());
      }
    };

    /*!
      \class Extract_include_directives
      \brief Enables read/write iterator access to the include directives from an istream.

      Extracting all include directives from an istream via a single pass forward iterator over IncludeDirective elements
      --- writing to these elements changes the underlying include directives. An ostream object contains the output. 
      Include directives resulting from macro replacement are not handled (since this depends on the context of the
      translation).

      \todo Design and implement. The algorithmic idea is to first check for lines of the form
      #include "*" or
      #include <*>
      (with spaces allowed according to  IncludeDirective); if found, then this is the value of the current 
      iterator, and the rest of the line is copied. Otherwise the line is scanned for an opening C-comment token:
      If found then the text is scanned for the closing token, and then as well as when the opening token is not found,
      that line is read until the end-of-line (and copied). Using ++ on the iterator writes the
      IncludeDirective to the ostream object.
    */

    class Extract_include_directives {};

    /*!
      \class Extend_include_directives
      \brief Functor for adding suitable prefixes to the include directives of an istream.

      The input is an istream and a form of an "associative prefix container". All include directives are extracted,
      checked whether they have a unique extension via the prefix container, if yes, they are extended, if not,
      a policy-controlled alternative action takes place.

      \todo Design and implement.
    */

    class Extend_include_directives {};

    /*!
      \class Extend_include_directives_Two_directories
      \brief Extend all include directives in files below some working directories with pathes relative to a working directory.

      Given a reference directory and a working directory, in all suitable files below the working
      directory suitable include directives including a file given via PATH are replaced by the similar
      include directive now including PREFIX/PATH, if, using the reference directory as base, this new
      path uniquely determines an existing file.

      \todo Design and implement. First the reference directory is recursively iterated (using a suitable
      iterator to be written an a new module "FileSystemTools") and the boost::path's obtained are
      put into an associative prefix container (regarding a path as a sequence, but in reverse
      order(!); the associative prefix container can be implemented in a new module "SearchDataStructures"
      as a simple wrapper around std::set, using lexicographical order and searching for an extension via
      std::set::lower_bound). Once that associative prefix container is filled, all suitable files under
      the working directory are handled by Extend_include_directives.
    */

    class Extend_include_directives_Two_directories {};

  }

}

#endif

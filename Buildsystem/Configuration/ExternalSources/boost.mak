# Oliver Kullmann, 21.8.2007 (Swansea)

# Settings for building and using the Boost library

boost_recommended_version_number ?= 1_34_1
boost_supported_not_recommended_version_numbers ?=
boost_supported_version_numbers ?= $(boost_supported_not_recommended_version_numbers) $(boost_recommended_version_number)

boost_prefix ?= boost

boost_base_directory ?= $(ExternalSources)/Boost

boost_recommended_package_name ?= $(boost_recommended_version_number)
# OK: The variable boost_recommended_package_name seems wrong, and seems
# to be used only for setting boost_html_documentation_index_location ??
boost_html_documentation_index_location ?= $(ExternalSources_doc)/Boost/$(boost_recommended_package_name)/index.htm

boost_homepage_url := http://www.boost.org/
boost_documentation_url := http://www.boost.org/libs/libraries.htm

boost_targets_prefix := $(boost_prefix)-
boost_prefix_underscore := $(boost_prefix)_
# OK: where do we use boost_prefix_underscore ??
boost_targets := $(addprefix $(boost_targets_prefix), $(boost_supported_version_numbers))
boost_recommended := $(boost_targets_prefix)$(boost_recommended_version_number)

ifndef Boost
  ifdef BOOST
    Boost = -I$(BOOST)
  else
    Boost = -I/usr/local/$(boost_recommended)
  endif
endif
# TODO: We must update and systematise the use of such variables!


file(REMOVE_RECURSE
  "correrTests.pdb"
  "correrTests"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/correrTests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

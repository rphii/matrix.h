
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

mat_mul = executable('mat_mul', 'mat-mul.c', dependencies: [m_dep])

test(mat_mul.name(), mat_mul)


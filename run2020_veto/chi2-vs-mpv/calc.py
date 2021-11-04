#!/usr/bin/env python3

import sympy as sp



#x^4 - 86 min

a, b, c, d, e, f = sp.symbols('a b c d e f')
pars = [a, b, c, d, e, f]
n = sp.symbols('n', integer=True)
i = sp.symbols('i')
x, y = sp.symbols('x y', cls=sp.IndexedBase) #cls=sp.Function
#x = sp.IndexedBase('x',i)


#S = n
S_x, S_x2, S_x3, S_x4, S_x5, S_x6, S_x7, S_x8, S_x9, S_x10, S_xy, S_x2y, S_x3y, S_x4y, S_x5y, S_y = sp.symbols('S_x S_x2 S_x3 S_x4 S_x5 S_x6 S_x7 S_x8 S_x9 S_x10 S_xy S_x2y S_x3y S_x4y S_x5y S_y' )





#cramer
#[ n     ,   S_x  ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5    ]    a        | S_y
#[ S_x   ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6    ]    b        | S_xy
#[ S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7    ] *  c  =     | S_x2y
#[ S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8    ]    d        | S_x3y
#[ S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9    ]    e        | S_x4y
#[ S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9  ,  S_x10   ]    f        | S_x5y


delta = sp.det(sp.Matrix([
    [ n     ,   S_x  ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5    ],
    [ S_x   ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6    ],
    [ S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7    ],
    [ S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8    ],
    [ S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9    ],
    [ S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9  ,  S_x10   ],
    ]))


a = sp.det(sp.Matrix([
    [ S_y    ,   S_x  ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5    ],
    [ S_xy   ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6    ],
    [ S_x2y  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7    ],
    [ S_x3y  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8    ],
    [ S_x4y  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9    ],
    [ S_x5y  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9  ,  S_x10   ],
    ]))

b = sp.det(sp.Matrix([
    [ n     ,  S_y    ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5    ],
    [ S_x   ,  S_xy   ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6    ],
    [ S_x2  ,  S_x2y  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7    ],
    [ S_x3  ,  S_x3y  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8    ],
    [ S_x4  ,  S_x4y  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9    ],
    [ S_x5  ,  S_x5y  ,  S_x7  ,  S_x8  ,  S_x9  ,  S_x10   ],
    ]))

c = sp.det(sp.Matrix([
    [ n     ,   S_x  ,  S_y    ,  S_x3  ,  S_x4  ,  S_x5    ],
    [ S_x   ,  S_x2  ,  S_xy   ,  S_x4  ,  S_x5  ,  S_x6    ],
    [ S_x2  ,  S_x3  ,  S_x2y  ,  S_x5  ,  S_x6  ,  S_x7    ],
    [ S_x3  ,  S_x4  ,  S_x3y  ,  S_x6  ,  S_x7  ,  S_x8    ],
    [ S_x4  ,  S_x5  ,  S_x4y  ,  S_x7  ,  S_x8  ,  S_x9    ],
    [ S_x5  ,  S_x6  ,  S_x5y  ,  S_x8  ,  S_x9  ,  S_x10   ],
    ]))

d = sp.det(sp.Matrix([
    [ n     ,   S_x  ,  S_x2  ,  S_y    ,  S_x4  ,  S_x5    ],
    [ S_x   ,  S_x2  ,  S_x3  ,  S_xy   ,  S_x5  ,  S_x6    ],
    [ S_x2  ,  S_x3  ,  S_x4  ,  S_x2y  ,  S_x6  ,  S_x7    ],
    [ S_x3  ,  S_x4  ,  S_x5  ,  S_x3y  ,  S_x7  ,  S_x8    ],
    [ S_x4  ,  S_x5  ,  S_x6  ,  S_x4y  ,  S_x8  ,  S_x9    ],
    [ S_x5  ,  S_x6  ,  S_x7  ,  S_x5y  ,  S_x9  ,  S_x10   ],
    ]))

e = sp.det(sp.Matrix([
    [ n     ,   S_x  ,  S_x2  ,  S_x3  ,  S_y    ,  S_x5    ],
    [ S_x   ,  S_x2  ,  S_x3  ,  S_x4  ,  S_xy   ,  S_x6    ],
    [ S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x2y  ,  S_x7    ],
    [ S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x3y  ,  S_x8    ],
    [ S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x4y  ,  S_x9    ],
    [ S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x5y  ,  S_x10   ],
    ]))

f = sp.det(sp.Matrix([
    [ n     ,   S_x  ,  S_x2  ,  S_x3  ,  S_x4  ,  S_y     ],
    [ S_x   ,  S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_xy    ],
    [ S_x2  ,  S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x2y   ],
    [ S_x3  ,  S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x3y   ],
    [ S_x4  ,  S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x4y   ],
    [ S_x5  ,  S_x6  ,  S_x7  ,  S_x8  ,  S_x9  ,  S_x5y   ],
    ]))



print(f'delta = {delta}')
print(f'a = ({a})/delta')
print(f'b = ({b})/delta')
print(f'c = ({c})/delta')
print(f'd = ({d})/delta')
print(f'e = ({e})/delta')
print(f'f = ({f})/delta')








def linreg():


    
    delta1 = (-S_x**2 + S_x2*n)
    delta2 = (-S_x**2*S_x4 + 2*S_x*S_x2*S_x3 - S_x2**3 + S_x2*S_x4*n - S_x3**2*n)
    delta3 = (-S_x**2*S_x4*S_x6 + S_x**2*S_x5**2 + 2*S_x*S_x2*S_x3*S_x6 - 2*S_x*S_x2*S_x4*S_x5 - 2*S_x*S_x3**2*S_x5 + 2*S_x*S_x3*S_x4**2 - S_x2**3*S_x6 + 2*S_x2**2*S_x3*S_x5 + S_x2**2*S_x4**2 - 3*S_x2*S_x3**2*S_x4 + S_x2*S_x4*S_x6*n - S_x2*S_x5**2*n + S_x3**4 - S_x3**2*S_x6*n + 2*S_x3*S_x4*S_x5*n - S_x4**3*n)
    delta4 = (-S_x**2*S_x4*S_x6*S_x8 + S_x**2*S_x4*S_x7**2 + S_x**2*S_x5**2*S_x8 - 2*S_x**2*S_x5*S_x6*S_x7 + S_x**2*S_x6**3 + 2*S_x*S_x2*S_x3*S_x6*S_x8 - 2*S_x*S_x2*S_x3*S_x7**2 - 2*S_x*S_x2*S_x4*S_x5*S_x8 + 2*S_x*S_x2*S_x4*S_x6*S_x7 + 2*S_x*S_x2*S_x5**2*S_x7 - 2*S_x*S_x2*S_x5*S_x6**2 - 2*S_x*S_x3**2*S_x5*S_x8 + 2*S_x*S_x3**2*S_x6*S_x7 + 2*S_x*S_x3*S_x4**2*S_x8 - 4*S_x*S_x3*S_x4*S_x6**2 + 2*S_x*S_x3*S_x5**2*S_x6 - 2*S_x*S_x4**3*S_x7 + 4*S_x*S_x4**2*S_x5*S_x6 - 2*S_x*S_x4*S_x5**3 - S_x2**3*S_x6*S_x8 + S_x2**3*S_x7**2 + 2*S_x2**2*S_x3*S_x5*S_x8 - 2*S_x2**2*S_x3*S_x6*S_x7 + S_x2**2*S_x4**2*S_x8 - 4*S_x2**2*S_x4*S_x5*S_x7 + 2*S_x2**2*S_x4*S_x6**2 + S_x2**2*S_x5**2*S_x6 - 3*S_x2*S_x3**2*S_x4*S_x8 + 2*S_x2*S_x3**2*S_x5*S_x7 + S_x2*S_x3**2*S_x6**2 + 4*S_x2*S_x3*S_x4**2*S_x7 - 2*S_x2*S_x3*S_x4*S_x5*S_x6 - 2*S_x2*S_x3*S_x5**3 - 3*S_x2*S_x4**3*S_x6 + 3*S_x2*S_x4**2*S_x5**2 + S_x2*S_x4*S_x6*S_x8*n - S_x2*S_x4*S_x7**2*n - S_x2*S_x5**2*S_x8*n + 2*S_x2*S_x5*S_x6*S_x7*n - S_x2*S_x6**3*n + S_x3**4*S_x8 - 2*S_x3**3*S_x4*S_x7 - 2*S_x3**3*S_x5*S_x6 + 3*S_x3**2*S_x4**2*S_x6 + 3*S_x3**2*S_x4*S_x5**2 - S_x3**2*S_x6*S_x8*n + S_x3**2*S_x7**2*n - 4*S_x3*S_x4**3*S_x5 + 2*S_x3*S_x4*S_x5*S_x8*n - 2*S_x3*S_x4*S_x6*S_x7*n - 2*S_x3*S_x5**2*S_x7*n + 2*S_x3*S_x5*S_x6**2*n + S_x4**5 - S_x4**3*S_x8*n + 2*S_x4**2*S_x5*S_x7*n + S_x4**2*S_x6**2*n - 3*S_x4*S_x5**2*S_x6*n + S_x5**4*n)
    delta5 = ()
    subs = {
        sp.summation(x[i],(i,1,n)) : S_x,
        sp.summation(x[i]**2,(i,1,n)) : S_x2,
        sp.summation(x[i]**3,(i,1,n)) : S_x3,
        sp.summation(x[i]**4,(i,1,n)) : S_x4,
        sp.summation(x[i]**5,(i,1,n)) : S_x5,
        sp.summation(x[i]**6,(i,1,n)) : S_x6,
        sp.summation(x[i]**7,(i,1,n)) : S_x7,
        sp.summation(x[i]**8,(i,1,n)) : S_x8,
        sp.summation(x[i]**9,(i,1,n)) : S_x9,
        sp.summation(x[i]**10,(i,1,n)) : S_x10,
        sp.summation(x[i]*y[i],(i,1,n)) : S_xy,
        sp.summation(x[i]**2*y[i],(i,1,n)) : S_x2y,
        sp.summation(x[i]**3*y[i],(i,1,n)) : S_x3y,
        sp.summation(x[i]**4*y[i],(i,1,n)) : S_x4y,
        sp.summation(x[i]**5*y[i],(i,1,n)) : S_x5y,
        sp.summation(y[i],(i,1,n)) : S_y,
    #       n: 'S'
            }
    
    
    
    func = a + b*x[i] +c*x[i]**2 + d*x[i]**3 + e*x[i]**4 + f*x[i]**5
    chi2 = sp.summation((func -y[i])**2, (i,1,n))
    #chi2 = sp.summation((a+x[i]*b + x[i]**2*c - y[i])**2, (i,1,n))
    #chi2 = sp.summation((a+x[i]*b - y[i])**2, (i,1,n))
    print('start')
    
    dxda = sp.diff(chi2, a); print('dxda')
    dxdb = sp.diff(chi2, b); print('dxdb')
    dxdc = sp.diff(chi2, c); print('dxdc')
    dxdd = sp.diff(chi2, d); print('dxdd')
    dxde = sp.diff(chi2, e); print('dxde')
    dxdf = sp.diff(chi2, f); print('dxdf')
    
    
    dxda = sp.factor_terms(dxda.expand().doit()).subs(subs)
    dxdb = sp.factor_terms(dxdb.expand().doit()).subs(subs)
    dxdc = sp.factor_terms(dxdc.expand().doit()).subs(subs)
    dxdd = sp.factor_terms(dxdd.expand().doit()).subs(subs)
    dxde = sp.factor_terms(dxde.expand().doit()).subs(subs)
    dxdf = sp.factor_terms(dxdf.expand().doit()).subs(subs)
    
    print('start linsolve')
    ress = sp.linsolve((
        dxda,
        dxdb,
        dxdc,
        dxdd,
        dxde,
        dxdf
        ), a,b,c, d, e, f)
    
    print('linsolve ended')
    
    
    res = ress.subs({
            delta1: 'delta1',
            delta2: 'delta2',
            delta3: 'delta3',
            delta4: 'delta4',
            delta5: 'delta5'
            })
    
    print('subs ended')
    
    print('start factor')
    
    res = sp.factor(res)
    
    print(f'delta1 = {delta1}')
    print(f'delta2 = {delta2}')
    print(f'delta3 = {delta3}')
    print(f'delta4 = {delta4}')
    print(f'delta5 = {delta5}')
    
    
    
#for l, eq in zip([a,b,c, d, e, f],next(iter(res))):
#    print(f'{l} = {eq}')

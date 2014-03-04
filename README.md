Cool Compiler
=============

Just your nancy pancy learning tool here. I'm learning about compilers and taking a class on
Coursera.

As a note, when I started this project I was using c++ < c++11, so I couldn't use the nice
`enum class { ... }` definitions. Unfortunately this means I had to use a hack if I wanted 
that functionality (which I did). I originally got the idea from [this site](http://bourt.com/blog/?p=372)
```
struct Join {
	enum E {
		Miter,
		Bevel,
		Round
	} e;
	Join(E e) : e(e) {}
	operator E() { return e; }
}
```

Also, static const multidimensional vectors. Eeek.

r0..r15
r0 1st argument
r1 2st argument 
r2 3rd argument
r3 saved by caller 
r4 saved by caller 
r5 saved by caller 
r6 saved by callie 
r7 saved by callie 
r8 stack pointer 
r9 frame pointer 
r10 return value  

int foo() {
    const int a; // Constant
    register int b; // PLUS UTILISÉ
    int f; // Allocation automatique
    auto int d; // Identique à la ligne du dessus
    static int c; // La variable est pas "exportable" et donc globale
    volatile int e;

    static const volatile f;
}
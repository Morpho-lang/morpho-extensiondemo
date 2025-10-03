#include <stdio.h>
#include <morpho.h>
#include <classes.h>

#include "extensiondemo.h"

/* -------------------------------------------------------
 * Example class definition
 * ------------------------------------------------------- */

/* @brief Example method 
   @param[in] v - the VM in use 
   @param[in] nargs - number of arguments passed
   @param[in] args - number of arguments passed (do not access these directly; use MORPHO_GETARG)
 */
value Foo_wibble(vm *v, int nargs, value *args) { 
    value slf = MORPHO_SELF(args); // Extract self from the arguments 
    morpho_printf(v, "Wibble.\n"); // Prints to virtual machine's stdout.

    return MORPHO_NIL; 
}

/** Now define the class using the following macros. In your initializer, you 
 *  will call builtin_addclass and provide this definition. */

MORPHO_BEGINCLASS(Foo)
MORPHO_METHOD(EXTENSIONDEMO_FOO_WIBBLE_METHOD, Foo_wibble, BUILTIN_FLAGSEMPTY)
MORPHO_ENDCLASS

/* -------------------------------------------------------
 * Example function definition
 * ------------------------------------------------------- */

/** A toy function that prints its arguments and returns an integer. 
 *  Note functions and methods have the same standard calling convention. */
value foo(vm *v, int nargs, value *args) {
    for (int i=0; i<nargs; i++) {
        value val = MORPHO_GETARG(args, i); // Use MORPHO_GETARG to get the correct parameter
        morpho_printvalue(v, val);
        morpho_printf(v, " ");
    }
    morpho_printf(v, "\n");

    return MORPHO_INT(1); // Return an integer value
}

/* -------------------------------------------------------
 * Initialization and finalization
 * ------------------------------------------------------- */

/* Initializer functions are recognized by Morpho from its name, 
   which must be LIBRARYNAME_initialize (replace LIBRARYNAME with the
   name of your extension). You may optionally provide finalizer functions
   to clean up resources outside of morpho on exit; use morpho_addfinalizefn
   to set these as shown below. */

/* The initializer function is called after the Dynamic library is
   imported. You should define any classes, functions or errors here;
   these are automatically deallocated for you upon exit. */
void extensiondemo_initialize(void) { 

    // Create the Foo class inheriting from the Object base class. 
    objectstring objclassname = MORPHO_STATICSTRING(OBJECT_CLASSNAME);
    value objclass = builtin_findclass(MORPHO_OBJECT(&objclassname));
    
    builtin_addclass(EXTENSIONDEMO_FOO_CLASSNAME, MORPHO_GETCLASSDEFINITION(Foo), objclass);

    builtin_addfunction(EXTENSIONDEMO_FOO_FNNAME, foo, BUILTIN_FLAGSEMPTY);

    morpho_addfinalizefn(extensiondemo_finalize); // Delete if not needed.
}

/* Finalizer functions are called as morpho terminates. 
   Free anything you allocated here, or release any system resources not
   associated with morpho. Delete if not needed. */
void extensiondemo_finalize(void) { 
}

// It is adamant that CODE is READABLE in a team project.
// This is how I write my code to keep it clear, but you
// don't have to copy (or even like) my style.

// ===================================================================

// VARIABLES AND FUNCTIONS

// cb_function()      Don't use obscure abbreviations.
// callback_function  I usually do this instead.





// int idx;           Don't use obscure simplifications of words
// int index;         I usually do this instead

// ===================================================================

// FUNCTION ARGUMENTS AND PARAMETERS

// void my_function(arg_1, arg_2, arg_3, arg_4, arg_5);  Don't make overly long function parameters.
//                                                       The human eye is better at looking up and down.
// void my_function(    
//	arg_1,                                               I do this instead. The only time I don't
//	arg_2,                                               do this is if the parameters are two or less.
//	arg_3,
//	arg_4,
//	arg_5);





// my_function(arg_1, arg_2, arg_3, arg_4, arg_5);       Same thing with function calls; Try to not do this
//
// my_function(                                          I do this instead.
//	arg_1,
//	arg_2,
//	arg_3,
//	arg_4,
//	arg_5);

// ===================================================================

// VARAIBLE AND FUNCTION CALL ALIGNMENT

// int variable_1 = 0;                  Try your best not to do this. This is a
// int my_variable_2 = 0;               maze for the eyes.
// int var_3 = 0;
// char my_character = 'a';
// float my_decimal = 0.0f;

// int   variable_1    = 0;             I do this instead. Notice the alignment for
// int   my_variable_2 = 0;             the variable names and assignment operators.
// int   var_3         = 0;
// char  my_character  = 'a';
// float my_decimal    = 0.0f;






// function_call(arg_1);                                Try your best not to do this.
// do_this_function();
// another_function_call(arg_2, arg_2, arg_3);
// cleanup();


// function_call    (arg_1);                             I usually do this instead. Notice how
// do_this_function ();                                  the one with more than three arguments is
//                                                       separated with line breaks.
// another_function_call(
//	arg_2, 
//	arg_2, 
//	arg_3);
//
// cleanup();

// ===================================================================

// BRACKETS

// int main (void){               Try to not do this. It makes it hard to track
//                                the brackets (and thus function scopes) as
// }                              you write more code.

// int main(void)                 I do this instead.
// {
//
// }


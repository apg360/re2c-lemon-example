typedef enum { FAIL, OK } Result;

struct scanner_state
{
    const char *cursor; //start
    const char *limit;  //end
    const char *marker;
};

struct scanner_token
{
    double num;
};


/*!re2c
    wsp    = [ \t\v\f\r\n]+;          // whitespace
    letter = [a-z]+;
    digit  = [1-9][0-9]*;
    number = [-+]?([0-9]+([.][0-9]*)?|[.][0-9]+)([Ee][-+]?[0-9]+)?;
*/

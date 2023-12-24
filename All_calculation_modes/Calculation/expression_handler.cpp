
void expression_Mathematic_handler(TokenStream &Stream, Mathematic_result &result) {

    if(create_or_set_varriable(Stream))
        return;
    
    double _result = third_order(Stream);

    result = Mathematic_result(_result);

}
 

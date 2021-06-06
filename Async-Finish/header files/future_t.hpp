enum STATUS{
    DONE, RUNNING, ERROR, PUSHED
};


template<typename ReturnType>
class future_t{
    public:
        ReturnType return_val; 
        STATUS status;
        future_t(ReturnType return_val): return_val(return_val), status(RUNNING){}
        future_t(): status(RUNNING){}
        future_t(future_t &t): return_val(t.return_val), status(t.status){}

        ReturnType get(){
            while(status == RUNNING || status == PUSHED){}
            return return_val;
        }
        STATUS get_status(){
            return status;
        }
};
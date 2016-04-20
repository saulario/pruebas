package org.fl.commons;

import javax.interceptor.AroundInvoke;
import javax.interceptor.InvocationContext;

public class LoggerInterceptor {

    /**
     * 
     * @param ic
     * @return 
     */
    @AroundInvoke
    public Object doIt(final InvocationContext ic) throws Throwable {
        Object o = null;
        
        return o;
    }
    
}

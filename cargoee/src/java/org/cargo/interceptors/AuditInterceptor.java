package org.cargo.interceptors;

import javax.interceptor.AroundInvoke;
import javax.interceptor.Interceptor;
import javax.interceptor.InvocationContext;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

@Audit
@Interceptor
public class AuditInterceptor {
    
    private static final Logger log = LogManager.getLogger(AuditInterceptor.class);
    
    @AroundInvoke
    public Object doAudit(final InvocationContext ctx) throws Exception {
        log.info("-----> Inicio");
        
        
        log.info("<----- Fin");
        return ctx.proceed();
    }
    
    
}

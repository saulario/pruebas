package org.cargo.interceptors;

import java.io.Serializable;
import javax.interceptor.AroundInvoke;
import javax.interceptor.Interceptor;
import javax.interceptor.InvocationContext;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

@Interceptor
@Audit
public class AuditInterceptor implements Serializable {
    
    private static final Logger log = LogManager.getLogger(AuditInterceptor.class);
    
    @AroundInvoke
    public Object doAudit(final InvocationContext ctx) throws Exception {
        log.info("-----> Inicio");
        

        
        log.info("<----- Fin");
        return ctx.proceed();
    }
    
    
}

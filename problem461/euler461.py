#Author: Bruce Hart <bruce.hart@gmail.com>

import time
import math

def f(n, k):
   return math.exp(k/n) - 1

def f_sum(n, a, b, c, d):
   return f(n, a) + f(n, b) + f(n, c) + f(n, d)

def g(a, b, c, d):
   return a**2 + b**2 + c**2 + d**2
    
def euler461():
   N = 10000.0
   a = 0.0
   b = 0.0
   c = 0.0
   d = 0.0
	
   bestFit = [99999.0, 0, 0, 0, 0]
	
   maxCoef = N * math.log(math.pi+1)
	
   while (a < maxCoef):
      b = 0.0
      c = 0.0 
      d = 0.0
	  
      while (b <= a):
         c = 0.0
         d = 0.0			

			
         while (c <= b):
            dest = -1.0 + math.pi - f_sum(N, a, b, c, 0.0)
                        
            if (dest > 0): 
               d = math.floor(N*math.log(dest))
            else:
               d = 0.0
               
            if (d < 0): d = 0.0
			
            while (d <= c):				
               err = math.pi - f_sum(N, a, b, c, d)                                           
			   
               if (math.fabs(err) < bestFit[0]):
                  bestFit[0] = math.fabs(err)
                  bestFit[1] = a
                  bestFit[2] = b
                  bestFit[3] = c
                  bestFit[4] = d
						
                  #print "New best fit (error = {0}) : {1}, {2}, {3}, {4}".format(err, a, b, c, d)
					
               d = d + 1	
               
               if (err < 0): break
            
            err = math.pi - f_sum(N, a, b, c+1, 0.0)
            if (err < 0 and math.fabs(err) > bestFit[0]): break
            
            c = c + 1		
         
         err = math.pi - f_sum(N, a, b+1, 0.0, 0.0)
         if (err < 0 and math.fabs(err) > bestFit[0]): break
         
         b = b + 1			
      a = a + 1
      if (a%10 == 0): print "a={0}".format(a)
	
   print "a = {0}, b = {1}, c = {2}, d = {3}".format(bestFit[1],bestFit[2],bestFit[3],bestFit[4])
   print "f_n(x) = {0}, error = {1}".format(f_sum(N,bestFit[1],bestFit[2],bestFit[3],bestFit[4]), bestFit[0])
   print "g({0}) = {1}\n".format(N, g(bestFit[1],bestFit[2],bestFit[3],bestFit[4]))

	
	

	
if __name__ == '__main__':
    time.clock()
    euler461()
    print "Executed in {0} sec".format(time.clock())

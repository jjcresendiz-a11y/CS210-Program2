/* loadbalancer.cpp
 *
 * Manage the CPU load by assigning next job to CPU with the least load
 */

#include "loadbalancer.h"

int loadbalancer::getTime()
{
   return systemTime;
}

void loadbalancer::incTime()
{
   systemTime++;
}
  
void loadbalancer::addRequest(request r)
{
   requestQueue.push(r);
   incTime();
}
  
request loadbalancer::getRequest()
{
   incTime();

   if (!requestQueue.empty())
   {
      request r = requestQueue.front();
      requestQueue.pop();
      return r;
   }

   return request{};
}

bool loadbalancer::isRequestQueueEmpty()
{
  
} 

int loadbalancer::getSize()
{
  
} 

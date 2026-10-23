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
      request r = requestQueue.front(); // queue
      //request r = requestQueue.top(); // priority_queue and stack
      requestQueue.pop();
      return r;
   }

   // Keep the method well-defined even if it is called on an empty queue.
   return request{};
}

bool loadbalancer::isRequestQueueEmpty()
{
   return requestQueue.empty();
} 

int loadbalancer::getSize()
{
   return static_cast<int>(requestQueue.size());
} 

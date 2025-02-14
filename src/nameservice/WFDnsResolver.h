/*
  Copyright (c) 2020 Sogou, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  Author: Xie Han (xiehan@sogou-inc.com)
*/

#ifndef _WFDNSRESOLVER_H_
#define _WFDNSRESOLVER_H_

#include "EndpointParams.h"
#include "WFNameService.h"
#include "WFResourcePool.h"

class WFDnsResolver : public WFNSPolicy
{
public:
	virtual WFRouterTask *create_router_task(const struct WFNSParams *params,
											 router_callback_t callback);

public:
	WFRouterTask *create(const struct WFNSParams *params, int dns_cache_level,
						 unsigned int dns_ttl_default, unsigned int dns_ttl_min,
						 const struct EndpointParams *endpoint_params,
						 router_callback_t&& callback);

private:
	WFResourcePool respool;

private:
	WFConditional *get_cond(SubTask *task)
	{
		static void *buf;
		return this->respool.get(task, &buf);
	}

	void post_cond() { this->respool.post(NULL); }

public:
	WFDnsResolver();
	friend class WFResolverTask;
};

#endif


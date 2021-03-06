/*******************************************************************************
*  Copyright (c) 1998 MFC Forum
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Module Name:
*
* Revision History:
*
* Date        Ver Name                    Description
* ----------  --- --------------------- -----------------------------------------
* 07-Jun-2016 0.1 Youngho Kim             Created
* ----------  --- --------------------- -----------------------------------------
*
* DESCRIPTION:
*
*  $Author:
*  $LastChangedBy:
*  $Date:
*  $Revision: 2949 $
*  $Id:
*  $HeadURL:
*******************************************************************************/
#include "ResponseBase.h"
#include "RestExceptionExt.h"

namespace rest {

ResponseBase* ResponseBase::m_Instance = NULL;

ResponseBase::ResponseBase()
{
	// TODO Auto-generated constructor stub
	ResponseBase::m_Instance = this;
}

ResponseBase::~ResponseBase() {
	// TODO Auto-generated destructor stub
}

ResponseBase* ResponseBase::getInstance()
{
	return ResponseBase::m_Instance;
}

bool ResponseBase::setResponse(const cpr::Response& res) throw (RestException, RestExceptionExt)
{
	bool parsingRet = false;
	m_response = res;

	if(m_response.status_code == 200) {
		Json::Reader reader;

		log_debug("response status code: %d", m_response.status_code);
		log_debug("response text: %s", m_response.text.c_str());

	    parsingRet = reader.parse(m_response.text, m_root);

	    if(m_response.status_code != 200) {
	    	log_error("Failed to request code: %d", m_response.status_code);

	    	throw RestException(m_response.status_code);
	    }

		if (!parsingRet) {
			log_error("Failed to parse Json : %s", reader.getFormattedErrorMessages().c_str());
			return parsingRet;
		}
	}

	return parsingRet;
}

int ResponseBase::getResponseStatusCode()
{
	return m_response.status_code;
}

} /* namespace rest */ //end of rest

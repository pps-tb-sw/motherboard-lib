#include "TDCControl.h"

void
TDCControl::Dump(int verb, std::ostream& os) const
{
  os << "===================="
     << " TDC Control register dump "
     << "===================" << std::endl;
  if (verb>1) DumpRegister(verb, os);
  os << " EnablePattern: " << GetEnablePattern() << std::endl
     << " Global reset: " << GetGlobalReset() << std::endl
     << " DLL reset: " << GetDLLReset() << std::endl
     << " PLL reset: " << GetPLLReset() << std::endl;
}

void
TDCControl::SetConstantValues()
{
  EnableAllChannels();
}

/*std::string
TDCControl::GetXML() const
{*/
  
  /*DOMElement* pRoot = p_DOMDocument->getDocumentElement();
  DOMElement* pEle = p_DOMDocument->createElement(L"richmediaAd");
  pRoot->appendChild(pEle);*/
  /*pEle->setAttribute(L"modelVersion", L"0.9");
  DOMText* pText = p_DOMDocument->createTextNode(L"yadda...yadda...");
  pEle->appendChild(pText);*/

  /*XMLString::transcode("FirstElement", tempStr, 99);
  DOMElement* first = doc->createElement(tempStr);
  root->appendChild(first);*/


  //DOMLSSerializer* theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();

  //FIXME for debugging
  //XMLFormatTarget *myFormTarget = new StdOutFormatTarget();
  //DOMLSOutput* theOutput = ((DOMImplementationLS*)impl)->createLSOutput();
  //theOutput->setByteStream(myFormTarget);

  //os << theSerializer->writeToString();
  /*std::ostringstream os;
  os << XMLHandler::WriteRegister(this);
  return os.str();
}*/

#include <src/ui/states/session-state.hpp>
#include <src/helpers/date-time.hpp>
#include <src/service/proxy/base-security-proxy.hpp>
#include <src/ui/ui-context.hpp>

void SessionState::render()
{

}

std::string SessionState::getPromptPrefix(UIContext& context) const
{
    return "[" + DateTime::now().toSring() + "]: " + context.getAuthService().getCurrentUsername()
        + "@" + BaseSecurityProxy::roleToString(context.getAuthService().getCurrentRole()) + " > ";
}

void SessionState::handleInput(UIContext& context, const std::string &input)
{

}

# import Triggers_util.py


def generateTriggersHeader(Triggers):
    out = ""
    for extern in Triggers.iter("extern"):
        out += "extern " + extern.attrib["type"] + " " + extern.attrib["id"] + ";\n"
    out += "State* eStopTrigger();\n"
    for trigger in Triggers.iter("trigger"):
        out += (
            "State* state"
            + trigger.attrib["currState"]
            + "To"
            + trigger.attrib["nextState"]
            + "Trigger();\n"
        )
    return out

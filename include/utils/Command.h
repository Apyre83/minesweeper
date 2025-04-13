#ifndef __COMMAND_H
#define __COMMAND_H

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};


#endif /* __COMMAND_H */

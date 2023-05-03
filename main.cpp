#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection.h>
#include <memory>
#include <optional>
#include "person.pb.h"

using pbPerson = demo::Person;

void PrintProtoMsg2(const google::protobuf::Message &message);

int main(int, char **)
{

    auto p1 = std::make_shared<pbPerson>();
    p1->set_name("xiaoming");
    p1->set_id(1);
    auto pn = p1->mutable_phone();
    pn->set_type(pbPerson::PhoneType::Person_PhoneType_MOBILE);
    pn->set_number("1111111");
    auto *book = p1->mutable_book();
    for (int i = 0; i < 5; i++)
    {
        auto *number = book->Add();
        number->set_type(pbPerson::PhoneType::Person_PhoneType_WORK);
        number->set_number(std::to_string(i * 11111));
    }
    for (int i = 0; i < 5; i++)
    {
        p1->add_friends("friends_" + std::to_string(i) + " 666.");
    }
    // p1->add_scores(100);

    std::cout << "Hello, world!\n";

    PrintProtoMsg2(*p1);

    return 0;
}

void PrintProtoMsg2(const google::protobuf::Message &message)
{
    using namespace google::protobuf;
    auto *descriptor = message.GetDescriptor();
    auto *reflection = message.GetReflection();
    // 遍历所有字段
    int fields = descriptor->field_count();
    for (int i = 0; i < fields; ++i)
    {
        auto *single_filed = descriptor->field(i);
        // 根据类型筛选
        // bool has_field = reflection->HasField(message, single_filed);
        // if (!has_field)
        // {
        //     continue;
        // }
        std::optional<int> repeated_counts = single_filed->is_repeated() ? reflection->FieldSize(message, single_filed) : std::optional<int>{};

        switch (single_filed->type())
        {
        case FieldDescriptor::TYPE_INT32:
        case FieldDescriptor::TYPE_SINT32:
        case FieldDescriptor::TYPE_FIXED32:
        {
            if (repeated_counts)
            {
                for (int j = 0; j < repeated_counts.value(); ++j)
                {
                    std::cout << " int32 repeated " << reflection->GetRepeatedInt32(message, single_filed, j) << "\n";
                }
            }
            else
            {
                std::cout << " int32 " << reflection->GetInt32(message, single_filed) << "\n";
            }
        }
        break;
        case FieldDescriptor::TYPE_STRING:
        case FieldDescriptor::TYPE_BYTES:
        {
            if (repeated_counts)
            {
                for (int j = 0; j < repeated_counts.value(); ++j)
                {
                    std::cout << " string repeated " << reflection->GetRepeatedString(message, single_filed, j) << "\n";
                }
            }
            else
            {
                std::cout << " string " << reflection->GetString(message, single_filed) << "\n";
            }
        }
        break;

        case FieldDescriptor::TYPE_ENUM:
        {
            if (repeated_counts)
            {
                for (int j = 0; j < repeated_counts.value(); ++j)
                {
                    auto *single_enum = reflection->GetRepeatedEnum(message, single_filed, j);
                    std::cout << " string repeated enum " << single_enum->full_name() << "\n";
                }
            }
            else
            {
                auto *single_enum = reflection->GetEnum(message, single_filed);
                std::cout << " string repeated enum " << single_enum->full_name() << "\n";
            }
        }
        break;
        case FieldDescriptor::TYPE_MESSAGE:
        {
            if (repeated_counts)
            {
                for (int j = 0; j < repeated_counts.value(); ++j)
                {
                    auto const &msg = reflection->GetRepeatedMessage(message, single_filed, j);
                    std::cout << " repeated msg " << j << "\n";
                    PrintProtoMsg2(msg);
                }
            }
            else
            {
                auto const &msg = reflection->GetMessage(message, single_filed);
                std::cout << " msg "
                          << "\n";
                PrintProtoMsg2(msg);
            }
        }
        break;
        default:
            break;
        }
    }
}

void PrintProtoMsg(const google::protobuf::Message &message)
{
    const google::protobuf::Descriptor *des = message.GetDescriptor();
    const google::protobuf::Reflection *ref = message.GetReflection();
    int fieldCount = des->field_count();
    for (int i = 0; i < fieldCount; i++)
    {
        ///< get field with index i
        const google::protobuf::FieldDescriptor *field = des->field(i);
        switch (field->type())
        {
        case google::protobuf::FieldDescriptor::Type::TYPE_INT32:
        case google::protobuf::FieldDescriptor::Type::TYPE_SINT32:
        case google::protobuf::FieldDescriptor::Type::TYPE_SFIXED32:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    int32_t data = ref->GetRepeatedInt32(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                int32_t data = ref->GetInt32(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_INT64:
        case google::protobuf::FieldDescriptor::Type::TYPE_SINT64:
        case google::protobuf::FieldDescriptor::Type::TYPE_SFIXED64:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    int64_t data = ref->GetRepeatedInt64(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                int64_t data = ref->GetInt64(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_UINT32:
        case google::protobuf::FieldDescriptor::Type::TYPE_FIXED32:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    uint32_t data = ref->GetRepeatedUInt32(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                uint32_t data = ref->GetUInt32(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_UINT64:
        case google::protobuf::FieldDescriptor::Type::TYPE_FIXED64:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    uint32_t data = ref->GetRepeatedUInt64(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                uint32_t data = ref->GetUInt64(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_DOUBLE:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    double data = ref->GetRepeatedDouble(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                double data = ref->GetDouble(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_FLOAT:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    float data = ref->GetRepeatedFloat(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                float data = ref->GetFloat(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_BOOL:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    bool data = ref->GetRepeatedBool(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                bool data = ref->GetBool(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_ENUM:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    const google::protobuf::EnumValueDescriptor *data = ref->GetRepeatedEnum(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                const google::protobuf::EnumValueDescriptor *data = ref->GetEnum(message, field);
                std::cout << data->number() << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_STRING:
        case google::protobuf::FieldDescriptor::Type::TYPE_BYTES:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    std::string data = ref->GetRepeatedString(message, field, j);
                    std::cout << data << ",";
                }
            }
            else
            {
                std::string data = ref->GetString(message, field);
                std::cout << data << ",";
            }
        }
        break;
        case google::protobuf::FieldDescriptor::Type::TYPE_MESSAGE:
        {
            if (field->is_repeated())
            {
                int count = ref->FieldSize(message, field);
                for (int j = 0; j < count; j++)
                {
                    const google::protobuf::Message &innerMsg = ref->GetRepeatedMessage(message, field, j);
                    PrintProtoMsg(innerMsg);
                }
            }
            else
            {
                const google::protobuf::Message &innerMsg = ref->GetMessage(message, field);
                PrintProtoMsg(innerMsg);
            }
        }
        break;
        default:
            break;
        }
    }
}
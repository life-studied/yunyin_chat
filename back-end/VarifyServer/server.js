const grpc = require("@grpc/grpc-js")
const message_proto = require("./proto")
const const_module = require("./const")
const {v4: uuidv4} = require('uuid');
const emailModule = require("./email");

async function GetVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try{
        uniqueId = uuidv4();
        console.log("uniqueId is ", uniqueId)
        let text_str =  '������֤��Ϊ'+ uniqueId +'�������������ע��'
        //�����ʼ�
        let mailOptions = {
            from: 'yunyin_jayyi@qq.com',
            to: call.request.email,
            subject: '��֤��',
            text: text_str,
        };
        let send_res = await emailModule.SendMail(mailOptions);
        console.log("send res is ", send_res)
        callback(null, { email:  call.request.email,
            error:const_module.Errors.Success
        }); 
    }catch(error){
        console.log("catch error is ", error)
        callback(null, { email:  call.request.email,
            error:const_module.Errors.Exception
        }); 
    }
}
function main() {
    var server = new grpc.Server()
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode })
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
        server.start()
        console.log('grpc server started')        
    })
}
main()
import * as dns from 'dns';
import ora from 'ora';
import chalk from 'chalk';
import PeaPod from './lib/PeaPod';

const sleep = (millis : number) => {
    return new Promise(resolve => {
        setTimeout(resolve, millis);
    });
};

const defaultSpinner : ora.Spinner = {
    interval: 50,
    frames: [
        "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁",
        "█▁▁▁▁▁▁▁▁▁▁▁▁▁▁",
        "██▁▁▁▁▁▁▁▁▁▁▁▁▁",
        "███▁▁▁▁▁▁▁▁▁▁▁▁",
        "████▁▁▁▁▁▁▁▁▁▁▁",
        "█████▁▁▁▁▁▁▁▁▁▁",
        "▁█████▁▁▁▁▁▁▁▁▁",
        "▁▁█████▁▁▁▁▁▁▁▁",
        "▁▁▁█████▁▁▁▁▁▁▁",
        "▁▁▁▁█████▁▁▁▁▁▁",
        "▁▁▁▁▁█████▁▁▁▁▁",
        "▁▁▁▁▁▁█████▁▁▁▁",
        "▁▁▁▁▁▁▁█████▁▁▁",
        "▁▁▁▁▁▁▁▁█████▁▁",
        "▁▁▁▁▁▁▁▁▁█████▁",
        "▁▁▁▁▁▁▁▁▁▁█████",
        "▁▁▁▁▁▁▁▁▁▁▁████",
        "▁▁▁▁▁▁▁▁▁▁▁▁███",
        "▁▁▁▁▁▁▁▁▁▁▁▁▁██",
        "▁▁▁▁▁▁▁▁▁▁▁▁▁▁█",
    ]
}

var loading : ora.Ora;

/**
 * Checks the internet connectivity.
 * @param {number} timeout Timeout in milliseconds.
 * @param {dns.Resolver} resolver DNS Resolver object.
 */
function checkInternet (timeout : number = 5000) : Promise<boolean> {
    const resolver = new dns.Resolver({timeout: timeout});
    return new Promise<boolean>(ret=>{
        resolver.resolve('www.google.com',err=> {
            if (err) {
                ret(false);
            } else {
                ret(true);
            }
        });
    });
}

async function main(){
    loading = ora({
        text: `Checking for ${chalk.blue('Internet')} connection...'`,
        spinner: defaultSpinner,
    }).start();

    if(!(await checkInternet(5))){
        loading.fail('Could not connect to the Internet.');
        return;
    }
    loading.succeed(`Connected to the ${chalk.blue('Internet')}!`);
    await sleep(1500);
    var peapod = new PeaPod();
    const user = await peapod.authenticate();
    await peapod.setup((msg : string, finished: boolean)=>{
        if(!loading.isSpinning){
            loading = ora({
                text: msg,
                spinner: defaultSpinner,
            }).start();
        }
        if(finished){
            loading.succeed(msg);
        } else {
            loading.text = msg;
        }
    })
    loading.succeed();
    peapod.arduino?.start((msg)=>{
        console.log(`[${chalk.magenta(msg.type.toUpperCase())}] - ${JSON.stringify(msg.msg)}`);
        peapod.firebase?.start((topic, msg)=>{
            console.log(`[${chalk.green(`SERVER - ${topic.toUpperCase}`)}] - "${msg}"`);
        }, (err)=>{
            console.log(`[${chalk.redBright(`SERVER - ERROR`)}] - "${err}"`);
        });
    })
}

main();
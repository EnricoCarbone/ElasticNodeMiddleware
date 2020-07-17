from Configuration import Configuration

# define your address for your bitfiles
S15_ADDRESS_1 =0x0
S15_ADDRESS_2 =0x90000

class BitfileConfigs:

    s15ConfigPart1 = None
    s15ConfigPart2 = None

    def __init__(self):
        # create a configuration for your bitfiles
        # for bazel run you have to write the absolute path
        # self.s15ConfigPart1 = Configuration("../bitfiles/s15_p1.bit", S15_ADDRESS_1, S15_ADDRESS_1)
        # self.s15ConfigPart2 = Configuration("../bitfiles/s15_p2.bit", S15_ADDRESS_2, S15_ADDRESS_2)
        self.s15ConfigPart1 = Configuration("/home/annika/projects-es/ElasticNodeMiddleware/bitfiles/s15_p1.bit", S15_ADDRESS_1, S15_ADDRESS_1)
        self.s15ConfigPart2 = Configuration("/home/annika/projects-es/ElasticNodeMiddleware/bitfiles/s15_p2.bit", S15_ADDRESS_2, S15_ADDRESS_2)
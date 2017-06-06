class Request():

    def __init__(self, addr, request):
        self._addr = addr
        self._request = request
        self._headers = {}

    def parseHeaders(self):
        self._headers = self._read_until(self._request)

    def _read_until(self, delimiter):
        pass

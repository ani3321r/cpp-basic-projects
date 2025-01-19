#ifndef NETWORKING_H
#define NETWORKING_H

#include <string>

class Networking {
public:
    /**
     * Fetch exchange rates or financial data from a given API.
     * @param currencyCode - The base currency (e.g., "USD").
     * @return JSON string containing exchange rate information.
     */
    static std::string fetchExchangeRates(const std::string& currencyCode);
};

#endif // NETWORKING_H
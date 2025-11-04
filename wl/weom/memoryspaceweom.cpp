#include "wl/weom/memoryspaceweom.h"


namespace wl {

constexpr AddressRange MemorySpaceWEOM::CONFIGURATION_REGISTERS;
constexpr AddressRange MemorySpaceWEOM::FLASH_MEMORY;
constexpr uint32_t MemorySpaceWEOM::ADDRESS_FLASH_REGISTERS_START;

// Control - 0x00xx
constexpr AddressRange MemorySpaceWEOM::DEVICE_IDENTIFICATOR;
constexpr AddressRange MemorySpaceWEOM::TRIGGER;
constexpr AddressRange MemorySpaceWEOM::STATUS;

// General - 0x01xx
constexpr AddressRange MemorySpaceWEOM::MAIN_FIRMWARE_VERSION;
constexpr AddressRange MemorySpaceWEOM::SHUTTER_TEMPERATURE;
constexpr AddressRange MemorySpaceWEOM::SERIAL_NUMBER_CURRENT;
constexpr AddressRange MemorySpaceWEOM::ARTICLE_NUMBER_CURRENT;

// Video - 0x02xx
constexpr AddressRange MemorySpaceWEOM::PALETTE_INDEX_CURRENT;
constexpr AddressRange MemorySpaceWEOM::FRAME_RATE_CURRENT;
constexpr AddressRange MemorySpaceWEOM::IMAGE_FLIP_CURRENT;
constexpr AddressRange MemorySpaceWEOM::VIDEO_FORMAT;
constexpr AddressRange MemorySpaceWEOM::IMAGE_FREEZE;
constexpr AddressRange MemorySpaceWEOM::TEST_PATTERN;

// NUC - 0x03xx
constexpr AddressRange MemorySpaceWEOM::NUC_UPDATE_MODE_CURRENT;
constexpr AddressRange MemorySpaceWEOM::NUC_MAX_PERIOD_CURRENT;
constexpr AddressRange MemorySpaceWEOM::NUC_ADAPTIVE_THRESHOLD_CURRENT;

// Filters - 0x06xx
constexpr AddressRange MemorySpaceWEOM::TIME_DOMAIN_AVERAGE_CURRENT;
constexpr AddressRange MemorySpaceWEOM::IMAGE_EQUALIZATION_TYPE_CURRENT;
constexpr AddressRange MemorySpaceWEOM::MGC_CONTRAST_BRIGHTNESS_CURRENT;
constexpr AddressRange MemorySpaceWEOM::AGC_NH_SMOOTHING_CURRENT;
constexpr AddressRange MemorySpaceWEOM::SPATIAL_MEDIAN_FILTER_ENABLE_CURRENT;
constexpr AddressRange MemorySpaceWEOM::LINEAR_GAIN_WEIGHT;
constexpr AddressRange MemorySpaceWEOM::CLIP_LIMIT;
constexpr AddressRange MemorySpaceWEOM::PLATEAU_TAIL_REJECTION;

// Presets - 0x0Axx
constexpr AddressRange MemorySpaceWEOM::SELECTED_PRESET_INDEX;
constexpr AddressRange MemorySpaceWEOM::CURRENT_PRESET_INDEX;
constexpr AddressRange MemorySpaceWEOM::SELECTED_ATTRIBUTE_AND_PRESET_INDEX;
constexpr AddressRange MemorySpaceWEOM::ATTRIBUTE_ADDRESS;
constexpr AddressRange MemorySpaceWEOM::NUMBER_OF_PRESETS_AND_ATTRIBUTES;
constexpr AddressRange MemorySpaceWEOM::SELECTED_PRESET_ID;
constexpr AddressRange MemorySpaceWEOM::CURRENT_PRESET_ID;


// Palettes data
constexpr unsigned MemorySpaceWEOM::PALETTES_FACTORY_MAX_COUNT;
constexpr unsigned MemorySpaceWEOM::PALETTES_USER_MAX_COUNT;
constexpr uint32_t MemorySpaceWEOM::PALETTE_NAME_SIZE;
constexpr AddressRange MemorySpaceWEOM::PALETTES_REGISTERS;

MemorySpaceWEOM::MemorySpaceWEOM(const etl::ivector<MemoryDescriptorWEOM>& memoryDescriptors) :
    m_memoryDescriptors(memoryDescriptors.begin(), memoryDescriptors.end())
{
}

etl::expected<MemoryDescriptorWEOM, Error> MemorySpaceWEOM::getMemoryDescriptor(const AddressRange& addressRange) const
{
    for (const auto& descriptor : m_memoryDescriptors)
    {
        if (descriptor.addressRange.contains(addressRange))
        {
            return descriptor;
        }
    }

    return etl::unexpected<Error>(Error::MEMORYSPACE__INVALID_ADDRESS);
}

const etl::ivector<MemoryDescriptorWEOM>& MemorySpaceWEOM::getMemoryDescriptors() const
{
    return m_memoryDescriptors;
}

MemorySpaceWEOM MemorySpaceWEOM::getDeviceSpace()
{
    etl::vector<MemoryDescriptorWEOM, 2> memoryDescriptors = {
        MemoryDescriptorWEOM{CONFIGURATION_REGISTERS, MemoryTypeWEOM::REGISTERS_CONFIGURATION},
        MemoryDescriptorWEOM{FLASH_MEMORY, MemoryTypeWEOM::FLASH_MEMORY},
    };
    return MemorySpaceWEOM(memoryDescriptors);

}

MemoryDescriptorWEOM::MemoryDescriptorWEOM(const AddressRange& addressRange, MemoryTypeWEOM type) :
    addressRange(addressRange),
    type(type),
    minimumDataSize(getMinimumDataSize(type)),
    maximumDataSize(getMaximumDataSize(type))
{
}

uint32_t MemoryDescriptorWEOM::getMinimumDataSize(MemoryTypeWEOM type)
{
    switch (type)
    {
    case MemoryTypeWEOM::REGISTERS_CONFIGURATION:
    case MemoryTypeWEOM::FLASH_MEMORY:
        return 4;
    }
    assert(false);
    return 0;
}

uint32_t MemoryDescriptorWEOM::getMaximumDataSize(MemoryTypeWEOM type)
{
    switch (type)
    {
    case MemoryTypeWEOM::REGISTERS_CONFIGURATION:
    case MemoryTypeWEOM::FLASH_MEMORY:
        return 4;

    }
    assert(false);
    return 0;
}

} // namespace wl

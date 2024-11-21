#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/skbuff.h>
#include <linux/dma-mapping.h>

#define DRV_NAME "simple_ethernet"

/* Simplified device data */
struct simple_ethernet_priv {
    struct net_device *net_dev;
    void __iomem *mmio_base;     // Mapped memory space for the NIC registers
    struct napi_struct napi;     // For interrupt-driven data handling
    int irq;
    struct pci_dev *pdev;
};

/* Open (start) the network interface */
static int simple_ethernet_open(struct net_device *net_dev) {
    struct simple_ethernet_priv *priv = netdev_priv(net_dev);
    // Enable the network device interrupts
    netif_start_queue(net_dev);
    return 0;
}

/* Stop the network interface */
static int simple_ethernet_stop(struct net_device *net_dev) {
    struct simple_ethernet_priv *priv = netdev_priv(net_dev);
    netif_stop_queue(net_dev);
    return 0;
}

/* Transmit data (sending packets) */
static netdev_tx_t simple_ethernet_start_xmit(struct sk_buff *skb, struct net_device *net_dev) {
    struct simple_ethernet_priv *priv = netdev_priv(net_dev);
    
    // Simulate transmission by freeing the buffer and printing a message
    dev_kfree_skb(skb);
    printk(KERN_INFO "simple_ethernet: packet transmitted\n");
    
    return NETDEV_TX_OK;
}

/* Receive data (called when data is available) */
static int simple_ethernet_poll(struct napi_struct *napi, int budget) {
    struct simple_ethernet_priv *priv = container_of(napi, struct simple_ethernet_priv, napi);
    struct net_device *net_dev = priv->net_dev;
    struct sk_buff *skb;

    // Simulate packet reception by allocating a buffer and sending dummy data
    skb = netdev_alloc_skb(net_dev, 1500);
    if (!skb) return 0;

    skb_put(skb, 100); // Simulate receiving 100 bytes of data
    skb->protocol = eth_type_trans(skb, net_dev);
    netif_receive_skb(skb);
    printk(KERN_INFO "simple_ethernet: packet received\n");

    napi_complete_done(napi, 1); // Mark NAPI operation as done
    return 0;
}

/* Set up net_device operations */
static const struct net_device_ops simple_ethernet_netdev_ops = {
    .ndo_open       = simple_ethernet_open,
    .ndo_stop       = simple_ethernet_stop,
    .ndo_start_xmit = simple_ethernet_start_xmit,
};

/* PCI probe function (called when device is found on PCI bus) */
static int simple_ethernet_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent) {
    struct net_device *net_dev;
    struct simple_ethernet_priv *priv;
    
    net_dev = alloc_etherdev(sizeof(struct simple_ethernet_priv));
    if (!net_dev) return -ENOMEM;
    
    priv = netdev_priv(net_dev);
    priv->pdev = pdev;
    priv->net_dev = net_dev;
    
    pci_enable_device(pdev); // Enable the PCI device
    priv->mmio_base = pci_iomap(pdev, 0, 0); // Memory-mapped IO region
    
    // Set up netdev operations and features
    net_dev->netdev_ops = &simple_ethernet_netdev_ops;
    netif_napi_add(net_dev, &priv->napi, simple_ethernet_poll, 64);
    
    // Register the network device with the kernel
    register_netdev(net_dev);
    pci_set_drvdata(pdev, net_dev);

    return 0;
}

/* PCI remove function (cleanup when the device is removed) */
static void simple_ethernet_pci_remove(struct pci_dev *pdev) {
    struct net_device *net_dev = pci_get_drvdata(pdev);
    struct simple_ethernet_priv *priv = netdev_priv(net_dev);
    
    unregister_netdev(net_dev);
    pci_iounmap(pdev, priv->mmio_base);
    free_netdev(net_dev);
}

/* PCI device ID table (matching devices to the driver) */
static const struct pci_device_id simple_ethernet_pci_ids[] = {
    { PCI_DEVICE(0x8086, 0x100E) },  // Example for Intel 82540EM
    { 0 }
};

/* PCI driver structure */
static struct pci_driver simple_ethernet_driver = {
    .name     = DRV_NAME,
    .id_table = simple_ethernet_pci_ids,
    .probe    = simple_ethernet_pci_probe,
    .remove   = simple_ethernet_pci_remove,
};

/* Module initialization and cleanup */
static int __init simple_ethernet_init(void) {
    return pci_register_driver(&simple_ethernet_driver);
}

static void __exit simple_ethernet_exit(void) {
    pci_unregister_driver(&simple_ethernet_driver);
}

module_init(simple_ethernet_init);
module_exit(simple_ethernet_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shashank Ingle");
MODULE_DESCRIPTION("A Simple Ethernet PCI Driver");
